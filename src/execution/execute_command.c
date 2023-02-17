/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:31:41 by vfries            #+#    #+#             */
/*   Updated: 2023/02/17 02:56:28 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include "minishell_signal.h"
#include "lexer.h"
#include "terminal.h"
#include "error.h"
#include "minishell_struct.h"
#include "exit_code.h"
#include "env_variables.h"
#include "execution.h"
#include "expansions.h"

static void	run_subshell(t_token *command, t_minishell *minishell,
				t_list *here_docs);
static void	run_command(t_token *command, char **envp);
static void	run_command_error(t_token *command);

void	execute_command(t_token *command, t_minishell *minishell,
			t_list *here_docs)
{
	if (command->type == BUILTIN)
		return (run_builtin(command, minishell, here_docs));
	if (open_and_dup_files(command->files, here_docs))
		return ;
	if (command->type == SUBSHELL)
		return (run_subshell(command, minishell, here_docs));
	if (command->type == EXECUTABLE)
		return (run_command(command,
				get_non_empty_envp(minishell->env_variables, command->name))); // TODO get_envp() before the fork
	else
		return (run_command(command,
				get_non_empty_envp(minishell->env_variables, command->name))); // TODO get_envp() before the fork
}

static void	run_subshell(t_token *command, t_minishell *minishell,
				t_list *here_docs)
{
	execute_commands(&command->subshell, minishell, &here_docs);
	ft_hm_clear(&minishell->env_variables, &free);
	signal_init_handling_inside_execution();
	if (terminal_restore(minishell->termios_save) < 0)
		exit_code(-1);
	exit(exit_code(GET));
}

#include <stdio.h>
static void	run_command(t_token *command, char **envp)
{
	execve(command->name, command->args, envp);
	ft_free_split(envp);
	if (command->name == NULL)
		exit(0);
	run_command_error(command);
}

static void	run_command_error(t_token *command)
{
	struct stat	stat_ptr;

	if (command->type == COMMAND)
	{
		print_error(command->args[0], NULL, "command not found");
		exit(127);
	}
	if (stat(command->name, &stat_ptr) != 0)
	{
		print_error(command->name, NULL, get_error());
		exit(127);
	}
	if (stat_ptr.st_mode & S_IFDIR)
	{
		print_error(command->name, NULL, "Is a directory");
		exit(126);
	}
	if (access(command->name, X_OK))
	{
		print_error(command->name, NULL, get_error());
		exit(126);
	}
	print_error(command->name, NULL, get_error());
	exit(-1);
}
