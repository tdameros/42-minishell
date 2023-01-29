/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/01/29 20:36:49 by vfries           ###   ########lyon.fr   */
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
static int		execute_pipes_sub_tokens(t_list *sub_tokens,
					t_hashmap env_variables, t_list **here_docs);
static pid_t	execute_piped_command(t_list *sub_tokens,
					t_hashmap env_variables, t_list **here_docs);
static void		execute_forked_pipe(t_token *command, t_hashmap env_variables,
					t_list *here_docs, int pipe_fd[2]);

int	execute_pipes(t_list **tokens, t_hashmap env_variables, t_list **here_docs)
{
	t_list	*sub_tokens;
	int		exit_code;
	pid_t	pid;

	sub_tokens = create_sub_tokens(tokens);
	pid = minishell_fork();
	if (pid == -1)
	{
		ft_lstclear(&sub_tokens, &free_token);
		print_error(get_name(*tokens), FORK_FAILED, get_error());
		return (-1);
	}
	if (pid == 0)
		exit(execute_pipes_sub_tokens(sub_tokens, env_variables, here_docs));
	// TODO skip here_docs
	ft_lstclear(&sub_tokens, &free_token);
	waitpid(pid, &exit_code, 0);
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

static int	execute_pipes_sub_tokens(t_list *sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	int		ret;
	pid_t	pid;

	if (sub_tokens->next == NULL)
		return (execute_command_no_pipe(&sub_tokens, env_variables, here_docs));
	pid = execute_piped_command(sub_tokens, env_variables, here_docs);
	ret = execute_pipes_sub_tokens(sub_tokens->next, env_variables, here_docs);
	ft_lstdelone(sub_tokens, &free_token);
	close(STDIN_FILENO);
	if (pid != -1)
		waitpid(pid, NULL, 0);
	return (ret);
}

static pid_t	execute_piped_command(t_list *sub_tokens,
				t_hashmap env_variables, t_list **here_docs)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		print_error(get_name(sub_tokens), PIPE_FAILED, get_error());
		return (-1);
	}
	pid = minishell_fork();
	if (pid == -1)
		print_error(get_name(sub_tokens), FORK_FAILED, get_error());
	else if (pid == 0)
		execute_forked_pipe(sub_tokens->content, env_variables, *here_docs,
			pipe_fd);
	else if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error(get_name(sub_tokens), PIPE_DUP2_FAILED, get_error());
	if (close(pipe_fd[0]) == -1)
		print_error(get_name(sub_tokens), PIPE_CLOSE_FAILED, get_error());
	if (close(pipe_fd[1]) == -1)
		print_error(get_name(sub_tokens), PIPE_CLOSE_FAILED, get_error());
	return (pid);
}

static void	execute_forked_pipe(t_token *command, t_hashmap env_variables,
				t_list *here_docs, int pipe_fd[2])
{
	int	need_to_exit;

	need_to_exit = 0;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_error(command->args[0], PIPE_DUP2_FAILED, get_error());
		need_to_exit = 1;
	}
	if (close(pipe_fd[0]) == -1)
	{
		print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		need_to_exit = 1;
	}
	if (close(pipe_fd[1]) == -1)
	{
		print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		need_to_exit = 1;
	}
	if (need_to_exit)
		exit(-1);
	execute_command(command, env_variables, here_docs);
	exit(*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE));
}
