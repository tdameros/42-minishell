/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:01:57 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 16:28:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "execution.h"
#include "lexer.h"
#include "exit_code.h"
#include "error.h"
#include "env_variables.h"

static int	save_io(char *command_name, int *io_save);
static int	close_io_save(char *command_name, int *io_save);
static void	restore_io_and_close_io_save(int *io_save, char *command_name);

void	run_builtin(t_token *command, t_hashmap env_variables,
				t_list *here_docs)
{
	int	io_save[2];

	if (save_io(command->args[0], io_save))
		return ;
	if (open_and_dup_files(command->files, here_docs))
		return (restore_io_and_close_io_save(io_save, command->args[0]));
	if (command->builtin == ECHO)
		echo(command->args);
	else if (command->builtin == CD)
		cd(command->args, env_variables);
	else if (command->builtin == PWD)
		pwd();
	else if (command->builtin == EXPORT)
		export(command->args, env_variables);
	else if (command->builtin == UNSET)
		unset(command->args, env_variables);
	else if (command->builtin == ENV)
		env(command->args, env_variables);
	restore_io_and_close_io_save(io_save, command->args[0]);
	if (command->builtin == EXIT)
		exit_builtin(command->args);
}

static int	save_io(char *command_name, int *io_save)
{
	int	ret;

	ret = 0;
	io_save[0] = dup(STDIN_FILENO);
	if (io_save[0] == -1)
	{
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	io_save[1] = dup(STDOUT_FILENO);
	if (io_save[1] == -1)
	{
		if (close(io_save[0]))
			print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	return (ret);
}

static int	close_io_save(char *command_name, int *io_save)
{
	int	ret;

	ret = 0;
	if (close(io_save[0]))
	{
		print_error(command_name, BUILTIN_CLOSE_FAILED, get_error());
		ret = -1;
	}
	if (close(io_save[1]))
	{
		print_error(command_name, BUILTIN_CLOSE_FAILED, get_error());
		ret = -1;
	}
	return (ret);
}

static void	restore_io_and_close_io_save(int *io_save, char *command_name)
{
	if (dup2(io_save[0], STDIN_FILENO) == -1)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		exit_code(-1);
	}
	if (dup2(io_save[1], STDOUT_FILENO) == -1)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		exit_code(-1);
	}
	if (close_io_save(command_name, io_save))
		exit_code(-1);
}
