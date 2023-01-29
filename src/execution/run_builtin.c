/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:01:57 by vfries            #+#    #+#             */
/*   Updated: 2023/01/29 01:30:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
#include "execution.h"
#include "lexer.h"
#include "error.h"
#include "env_variables.h"

static int	save_io(char *command_name, int *io_save, t_hashmap env_variables);
static int	close_io_save(char *command_name, int *io_save);
static void	restore_io_and_close_io_save(int *io_save, char *command_name,
				t_hashmap env_variables);

void	run_builtin(t_token *command, t_hashmap env_variables,
				t_list *here_docs)
{
	int	io_save[2];

	if (save_io(command->args[0], io_save, env_variables))
		return ;
	if (open_and_dup_files(command->files, env_variables, here_docs))
	{
		close_io_save(command->args[0], io_save);
		return ;
	}
	if (command->builtin == ECHO)
		echo(command->args, env_variables);
	else if (command->builtin == CD)
		cd(command->args, env_variables);
	else if (command->builtin == PWD)
		pwd(env_variables);
	else if (command->builtin == EXPORT)
		export(command->args, env_variables);
	else if (command->builtin == UNSET)
		unset(command->args, env_variables);
	else if (command->builtin == ENV)
		env(command->args, env_variables);
	restore_io_and_close_io_save(io_save, command->args[0], env_variables);
	if (command->builtin == EXIT)
		exit_builtin(command->args, env_variables);
}

static int	save_io(char *command_name, int *io_save, t_hashmap env_variables)
{
	int	ret;

	ret = 0;
	io_save[0] = dup(STDIN_FILENO);
	if (io_save[0] == -1)
	{
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = -1;
		ret = -1;
	}
	io_save[1] = dup(STDOUT_FILENO);
	if (io_save[1] == -1)
	{
		if (close(io_save[0]))
			print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = -1;
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

static void	restore_io_and_close_io_save(int *io_save, char *command_name,
				t_hashmap env_variables)
{
	if (dup2(io_save[0], STDIN_FILENO) == -1)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = -1;
	}
	if (dup2(io_save[1], STDOUT_FILENO) == -1)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = -1;
	}
	if (close_io_save(command_name, io_save))
		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = -1;
}
