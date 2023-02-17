/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/17 02:49:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include "minishell_signal.h"
#include "minishell_struct.h"
#include "terminal.h"
#include "expansions.h"
#include "exit_code.h"
#include <sys/wait.h>
#include <stdlib.h>

static void		execute_commands_loop(t_list **tokens, t_minishell *minishell,
					t_list **here_docs);
static void		execute_command_no_pipe_builtin(t_list *command,
					t_minishell *minishell, t_list **here_docs);
static pid_t	fork_and_execute_command(t_token *command,
					t_minishell *minishell, t_list *here_docs);

void	execute_commands(t_list **tokens, t_minishell *minishell,
			t_list **here_docs)
{
	if (terminal_restore(minishell->termios_save) < 0)
	{
		exit_code(-1);
		return ;
	}
	signal_init_handling_inside_execution();
	execute_commands_loop(tokens, minishell, here_docs);
	ft_lstclear(tokens, &free_token);
	ft_lst_of_lst_clear(here_docs, &free);
	signal_init_handling_outside_execution();
	if (terminal_disable_ctrl_backslash_output() < 0)
	{
		exit_code(-1);
		return ;
	}
}

static void	execute_commands_loop(t_list **tokens, t_minishell *minishell,
				t_list **here_docs)
{
	while (*tokens != NULL)
	{
		if (get_next_operator(*tokens) == PIPE)
			execute_pipes(tokens, minishell, here_docs);
		else
			execute_command_no_pipe(tokens, minishell, here_docs);
		if (*tokens != NULL)
			get_next_command(tokens, exit_code(GET));
	}
}

void	execute_command_no_pipe(t_list **tokens, t_minishell *minishell,
		t_list **here_docs)
{
	int		exit_status;
	t_list	*command;
	t_token	*command_token;
	pid_t	pid;

	command = NULL;
	ft_lst_push(&command, tokens);
	command_token = command->content;
	if (command_token->type != SUBSHELL && apply_token_expansion(command_token,
			*here_docs, minishell->env_variables) < 0)
		return (print_error(command_token->name, NULL, get_error()));
	if (command_token->type == BUILTIN)
		return (execute_command_no_pipe_builtin(command, minishell, here_docs));
	pid = fork_and_execute_command(command->content, minishell, *here_docs);
	skip_token_here_docs(command, here_docs);
	ft_lstclear(&command, &free_token);
	if (pid == -1)
	{
		exit_code(-1);
		return ;
	}
	if (waitpid(pid, &exit_status, 0) >= 0)
		exit_code(WEXITSTATUS(exit_status));
}

static void	execute_command_no_pipe_builtin(t_list *command,
				t_minishell *minishell, t_list **here_docs)
{
	execute_command(command->content, minishell, *here_docs);
	skip_token_here_docs(command, here_docs);
	ft_lstclear(&command, &free_token);
	exit_code(GET);
}

static pid_t	fork_and_execute_command(t_token *command,
					t_minishell *minishell, t_list *here_docs)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error(command->args[0], FORK_FAILED, get_error());
		return (-1);
	}
	if (pid != 0)
		return (pid);
	execute_command(command, minishell, here_docs);
	exit(exit_code(GET));
}
