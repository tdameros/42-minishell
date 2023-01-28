/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 18:24:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_fork.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include <sys/wait.h>
#include <stdlib.h>

static t_list	*create_sub_tokens(t_list **tokens);
static void		execute_pipes_sub_tokens(t_list *sub_tokens,
					t_hashmap env_variables, t_list **here_docs);
static void		execute_piped_command(t_list *sub_tokens,
					t_hashmap env_variables, t_list **here_docs);
static void		execute_forked_pipe(t_token *command, t_hashmap env_variables,
					t_list *here_docs, int pipe_fd[2]);

int	execute_pipes(t_list **tokens, t_hashmap env_variables, t_list **here_docs)
{
	t_list	*sub_tokens;
	int		exit_code;
	pid_t	pid;

	// print_tokens(*tokens);
	// ft_printf("======================");
	sub_tokens = create_sub_tokens(tokens);
	// print_tokens(sub_tokens);
	pid = minishell_fork();
	if (pid == -1)
	{
		ft_lstclear(&sub_tokens, &free_token);
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
		if (token->type == OPERATOR && token->operator != PIPE)
			return (ft_lst_reverse(&sub_tokens));
		else if (token->operator == PIPE)
			ft_lst_get_next_free_current(tokens, &free_token);
		else
			ft_lst_push(&sub_tokens, tokens);
	}
	return (ft_lst_reverse(&sub_tokens));
}

static void	execute_pipes_sub_tokens(t_list *sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	if (sub_tokens == NULL) //TODO Remove this
		ft_printf("sub_tokens == NULL\n");
	while (sub_tokens->next != NULL)
	{
		// print_tokens(sub_tokens);
		// ft_printf("\n\n");
		// ft_printf("EXIT == %d\n\n", *(int *)ft_hm_get_content(env_variables,
		// 		LAST_EXIT_CODE));
		execute_piped_command(sub_tokens, env_variables, here_docs);
		sub_tokens = sub_tokens->next;
	}
	execute_command(sub_tokens->content, env_variables, *here_docs);
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
		print_error(get_name(sub_tokens), FORK_FAILED, get_error());
	else if (pid == 0)
		execute_forked_pipe(sub_tokens->content, env_variables, *here_docs,
			pipe_fd);
	else if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error(get_name(sub_tokens), PIPE_DUP2_FAILED, get_error());
	if (close(pipe_fd[0]) || close(pipe_fd[1]))
		print_error(get_name(sub_tokens), PIPE_CLOSE_FAILED, get_error());
}

static void	execute_forked_pipe(t_token *command, t_hashmap env_variables,
				t_list *here_docs, int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_error(command->args[0], PIPE_DUP2_FAILED, get_error());
		if (close(pipe_fd[0]) || close(pipe_fd[1]))
			print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		exit(-1);
	}
	if (close(pipe_fd[0]) || close(pipe_fd[1]))
	{
		print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		exit(-1);
	}
	execute_command(command, env_variables, here_docs);
	exit(*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE));
}
