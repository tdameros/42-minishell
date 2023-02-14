/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 23:59:33 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include "exit_code.h"
#include "expansions.h"
#include <sys/wait.h>
#include <stdlib.h>

static t_list	*create_sub_tokens(t_list **tokens);
static int		execute_pipes_sub_tokens(t_list *sub_tokens,
					t_minishell *minishell, t_list **here_docs);
static pid_t	execute_piped_command(t_list *sub_tokens,
					t_minishell *minishell, t_list **here_docs);
static int		execute_forked_pipe(t_token *command, t_minishell *minishell,
					t_list *here_docs, int pipe_fd[2]);

void	execute_pipes(t_list **tokens, t_minishell *minishell,
			t_list **here_docs)
{
	t_list	*sub_tokens;
	int		exit_status;
	pid_t	pid;

	sub_tokens = create_sub_tokens(tokens);
	pid = fork();
	if (pid == -1)
	{
		ft_lstclear(&sub_tokens, &free_token);
		print_error(get_name(*tokens), FORK_FAILED, get_error());
		exit_code(-1);
		return ;
	}
	if (pid == 0)
		exit(execute_pipes_sub_tokens(sub_tokens, minishell, here_docs));
	skip_tokens_here_docs(sub_tokens, here_docs);
	ft_lstclear(&sub_tokens, &free_token);
	if (waitpid(pid, &exit_status, 0) >= 0)
		exit_code(WEXITSTATUS(exit_status));
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
				t_minishell *minishell, t_list **here_docs)
{
	int		ret;
	pid_t	pid;

	if (sub_tokens->next == NULL)
	{
		execute_command_no_pipe(&sub_tokens, minishell, here_docs);
		return (exit_code(GET));
	}
	pid = execute_piped_command(sub_tokens, minishell, here_docs);
	skip_token_here_docs(sub_tokens, here_docs);
	ret = execute_pipes_sub_tokens(sub_tokens->next, minishell, here_docs);
	ft_lstdelone(sub_tokens, &free_token);
	close(STDIN_FILENO);
	if (pid != -1)
		waitpid(pid, NULL, 0);
	return (ret);
}

static pid_t	execute_piped_command(t_list *sub_tokens,
				t_minishell *minishell, t_list **here_docs)
{
	pid_t	pid;
	int		pipe_fd[2];
	t_token	*command_token;

	if (pipe(pipe_fd) == -1)
	{
		print_error(get_name(sub_tokens), PIPE_FAILED, get_error());
		return (-1);
	}
	command_token = sub_tokens->content;
	if (command_token->type != SUBSHELL && apply_token_expansion(command_token,
			*here_docs, minishell->env_variables) < 0)
		return (print_error(command_token->name, NULL, get_error()), -1);
	pid = fork();
	if (pid == -1)
		print_error(get_name(sub_tokens), FORK_FAILED, get_error());
	else if (pid == 0)
		exit(execute_forked_pipe(command_token, minishell, *here_docs,
				pipe_fd));
	else if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		print_error(get_name(sub_tokens), PIPE_DUP2_FAILED, get_error());
	if (close(pipe_fd[0]) == -1)
		print_error(get_name(sub_tokens), PIPE_CLOSE_FAILED, get_error());
	if (close(pipe_fd[1]) == -1)
		print_error(get_name(sub_tokens), PIPE_CLOSE_FAILED, get_error());
	return (pid);
}

static int	execute_forked_pipe(t_token *command, t_minishell *minishell,
				t_list *here_docs, int pipe_fd[2])
{
	bool	dont_execute_command;

	dont_execute_command = false;
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_error(command->args[0], PIPE_DUP2_FAILED, get_error());
		dont_execute_command = true;
	}
	if (close(pipe_fd[0]) == -1)
	{
		print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		dont_execute_command = true;
	}
	if (close(pipe_fd[1]) == -1)
	{
		print_error(command->args[0], PIPE_CLOSE_FAILED, get_error());
		dont_execute_command = true;
	}
	if (dont_execute_command)
		return (-1);
	execute_command(command, minishell, here_docs);
	return (exit_code(GET));
}
