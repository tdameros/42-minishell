/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_piped_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 16:42:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "error.h"
#include "minishell_signal.h"
#include "expansions.h"
#include "minishell_struct.h"
#include "execution.h"
#include "exit_code.h"
#include "env_variables.h"

static int			execute_piped_command_fork(t_minishell *minishell,
						t_list **tokens, int pipe_fd[2], char **envp);
static void			execute_piped_command_main_process(t_list **sub_tokens,
						t_minishell *minishell, int pipe_fd[2], char **envp);
static t_minishell	*get_piped_command_minishell(t_minishell *minishell,
						t_list *tokens);

pid_t	execute_piped_command(t_minishell *minishell,
					t_list **sub_tokens)
{
	pid_t	pid;
	int		pipe_fd[2];
	t_token	*command;
	char	**envp;

	if (pipe(pipe_fd) == -1)
		return (print_error(get_name(*sub_tokens), PIPE_FAILED, get_error()),
			-1);
	command = (*sub_tokens)->content;
	if (apply_token_expansion(command, minishell->here_docs,
			minishell->env_variables) < 0)
		return (print_error(command->args[0], NULL, get_error()), -1);
	envp = NULL;
	if (command->type != BUILTIN && command->type != SUBSHELL)
		envp = get_non_empty_envp(minishell->env_variables, command->args[0]);
	pid = execution_fork();
	if (pid == -1)
		print_error(command->args[0], FORK_FAILED, get_error());
	else if (pid == 0)
		exit(execute_piped_command_fork(minishell, sub_tokens, pipe_fd, envp));
	execute_piped_command_main_process(sub_tokens, minishell, pipe_fd, envp);
	if (pid == -1)
		exit_code(-1);
	return (pid);
}

static int	execute_piped_command_fork(t_minishell *minishell, t_list **tokens,
				int pipe_fd[2], char **envp)
{
	t_token	*command;
	bool	dont_execute_command;

	command = (*tokens)->content;
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
		return (exit_code(-1));
	execute_command(
		get_piped_command_minishell(minishell, *tokens), command, envp);
	return (exit_code(GET));
}

static void	execute_piped_command_main_process(t_list **sub_tokens,
				t_minishell *minishell, int pipe_fd[2], char **envp)
{
	ft_free_split(envp);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		print_error(get_name(*sub_tokens), PIPE_DUP2_FAILED, get_error());
		exit_code(-1);
	}
	if (close(pipe_fd[0]) == -1)
	{
		print_error(get_name(*sub_tokens), PIPE_CLOSE_FAILED, get_error());
		exit_code(-1);
	}
	if (close(pipe_fd[1]) == -1)
	{
		print_error(get_name(*sub_tokens), PIPE_CLOSE_FAILED, get_error());
		exit_code(-1);
	}
	skip_token_here_docs((*sub_tokens)->content, &minishell->here_docs);
	ft_lst_get_next_free_current(sub_tokens, &free_token);
}

static t_minishell	*get_piped_command_minishell(t_minishell *minishell,
			t_list *tokens)
{
	ft_lstclear(&minishell->tokens, &free_token);
	minishell->tokens = tokens;
	return (minishell);
}
