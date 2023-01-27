/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 13:34:01 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_fork.h"

int	execute_pipes(t_list **tokens, t_hashmap env_variables, t_list **here_docs)
{
	t_list	*sub_tokens;
	int		exit_code;
	pid_t	pid;

	create_sub_tokens(&sub_tokens, tokens);
	pid = minishell_fork();
	if (pid == 0)
		execute_pipes_sub_tokens(&sub_tokens, env_variables, here_docs);
	// TODO skip here_docs
	ft_lstclear(&sub_tokens, &free_token);
	wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}

static void	create_sub_tokens(t_list **sub_tokens, t_list **tokens)
{
	int		parentheses;
	t_token	*token;

	*sub_tokens = NULL;
	if (tokens == NULL)
		return (NULL);
	parentheses = 0;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type == OPERATOR
			&& token->operator != PIPE)
			return (ft_lst_reverse(sub_tokens));
		ft_lst_push(sub_tokens, tokens);
	}
	return (ft_lst_reverse(sub_tokens));
}

static int	execute_pipes_sub_tokens(t_list **sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	int	exit_code;

	while (get_next_operator(*sub_tokens) != -1)
	{
		execute_piped_command(sub_tokens, env_variables,
				here_docs);
		ft_lst_get_next_free_current(sub_tokens, &free_token);
	}
	execute_command(*sub_tokens, env_variables, here_docs, -1);
}

static void	execute_piped_command(t_list **sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	pid_t	pid;
	t_list	*command;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	command = get_command(sub_tokens);
	pid = minishell_fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return ;
	}
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(command, env_variables, here_docs, -1);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}
