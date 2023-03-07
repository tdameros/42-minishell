/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:31:41 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 18:06:44 by vfries           ###   ########lyon.fr   */
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

static void	run_subshell(t_minishell *minishell, t_token *command);
static void	run_command(t_minishell *minishell, t_token *command, char **envp);
static void	run_command_error(t_minishell *minishell, t_token *command);
static int	print_error_get_error_code(t_token *command);

void	execute_command(t_minishell *minishell, t_token *command, char **envp)
{
	int	io_redirection;

	if (command->type == BUILTIN)
		return (run_builtin(minishell, command));
	io_redirection = open_and_dup_files(command->files, minishell);
	if (io_redirection != 0)
	{
		if (io_redirection < 0)
			exit_code(-1);
		return ;
	}
	if (command->type == SUBSHELL)
		return (run_subshell(minishell, command));
	return (run_command(minishell, command, envp));
}

static void	run_subshell(t_minishell *minishell, t_token *command)
{
	t_list	*tmp;

	tmp = command->subshell;
	command->subshell = NULL;
	ft_lstclear(&minishell->tokens, &free_token);
	minishell->tokens = tmp;
	execute_commands(minishell);
	free_minishell(minishell);
	if (signal_init_handling_inside_execution())
		exit_code(-1);
	if (terminal_restore(minishell->termios_save) < 0)
		exit_code(-1);
	exit(exit_code(GET));
}

static void	run_command(t_minishell *minishell, t_token *command, char **envp)
{
	execve(command->name, command->args, envp);
	ft_free_split(envp);
	if (command->name == NULL)
	{
		free_minishell(minishell);
		exit(0);
	}
	run_command_error(minishell, command);
}

static void	run_command_error(t_minishell *minishell, t_token *command)
{
	int	ret;

	ret = print_error_get_error_code(command);
	free_minishell(minishell);
	(void)minishell;
	exit(ret);
}

static int	print_error_get_error_code(t_token *command)
{
	struct stat	stat_ptr;

	if (ft_strcmp(command->name, COMMAND_NOT_FOUND) == 0
		|| command->type == COMMAND)
	{
		print_error(command->args[0], NULL, "command not found");
		return (127);
	}
	else if (stat(command->name, &stat_ptr) != 0)
	{
		print_error(command->name, NULL, get_error());
		return (127);
	}
	else if (stat_ptr.st_mode & S_IFDIR)
	{
		print_error(command->name, NULL, "Is a directory");
		return (126);
	}
	else if (access(command->name, X_OK))
	{
		print_error(command->name, NULL, get_error());
		return (126);
	}
	print_error(command->name, NULL, get_error());
	return (-1);
}
