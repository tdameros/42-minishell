/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 08:10:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_fork.h"
#include "error.h"
#include "env_variables.h"

int	execute_pipes(t_list **tokens, t_hashmap env_variables, t_list **here_docs)
{
	t_list	*sub_tokens;
	int		exit_code;
	pid_t	pid;

	sub_tokens = create_sub_tokens(tokens);
	pid = minishell_fork();
	if (pid == -1)
	{
		print_error(get_name(*tokens), FORK_FAILED, get_error());
		return (-1);
	}
	if (pid == 0)
		execute_pipes_sub_tokens(sub_tokens, env_variables, here_docs);
	// TODO skip here_docs
	ft_lstclear(&sub_tokens, &free_token);
	wait(&exit_code); // TODO wait for all the forks
	return (WEXITSTATUS(exit_code));
}

static t_list	*create_sub_tokens(t_list **tokens)
{
	t_list	*sub_tokens;
	t_token	*token;

	sub_tokens = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPERATOR
			&& token->operator != PIPE)
			return (ft_lst_reverse(&sub_tokens));
		else if (token->type == PIPE)
			ft_lst_get_next_free_current(tokens, &free_token);
		else
			ft_lst_push(&sub_tokens, tokens);
	}
	return (ft_lst_reverse(&sub_tokens));
}

static int	execute_pipes_sub_tokens(t_list *sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	while (sub_tokens->next != NULL)
	{
		execute_piped_command(sub_tokens, env_variables, here_docs);
		sub_tokens = sub_tokens->next;
	}
	execute_command(sub_tokens, env_variables, here_docs);
}

static void	execute_piped_command(t_list *sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (print_error(get_name(sub_tokens), PIPE_FAILED, get_error()));
	pid = minishell_fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (print_error(get_name(sub_tokens), FORK_FAILED, get_error()));
	}
	if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(sub_tokens, env_variables, here_docs);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}
