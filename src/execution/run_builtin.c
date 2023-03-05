/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:01:57 by vfries            #+#    #+#             */
/*   Updated: 2023/02/15 00:29:51 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "execution.h"
#include "lexer.h"
#include "exit_code.h"

static int	prep_io(int *io_save, t_minishell *minishell, t_token *command);

void	run_builtin(t_minishell *minishell, t_token *command)
{
	int	io_save[2];

	if (prep_io(io_save, minishell, command) < 0)
		return ;
	if (command->builtin == ECHO_CMD)
		echo(command->args);
	else if (command->builtin == CD)
		cd(command->args, minishell->env_variables);
	else if (command->builtin == PWD)
		pwd(minishell->env_variables);
	else if (command->builtin == EXPORT)
		export(command->args, minishell->env_variables);
	else if (command->builtin == UNSET)
		unset(command->args, minishell->env_variables);
	else if (command->builtin == ENV)
		env(command->args, minishell->env_variables);
	if (restore_io_and_close_io_save(io_save, command->args[0]) < 0)
		exit_code(-1);
	if (command->builtin == EXIT)
		exit_builtin(command->args, minishell);
}

static int	prep_io(int *io_save, t_minishell *minishell, t_token *command)
{
	int	io_redirection;

	if (save_io(command->args[0], io_save))
	{
		exit_code(-1);
		return (-1);
	}
	io_redirection = open_and_dup_files(command->files, minishell);
	if (io_redirection != 0)
	{
		restore_io_and_close_io_save(io_save, command->args[0]);
		if (io_redirection < 0)
			exit_code(-1);
		return (-1);
	}
	return (0);
}
