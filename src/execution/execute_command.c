/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:31:41 by vfries            #+#    #+#             */
/*   Updated: 2023/01/30 00:30:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdlib.h>
#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include "minishell_fork.h"

static void	run_subshell(t_token *command, t_hashmap env_variables,
				t_list *here_docs);
static void	run_command(t_token *command, char **envp);
static void	run_command_error(t_token *command);

void	execute_command(t_token *command, t_hashmap env_variables,
			t_list *here_docs)
{
	// TODO fix_token_variables()
	if (command->type == BUILTIN)
		return (run_builtin(command, env_variables, here_docs));
	if (open_and_dup_files(command->files, env_variables, here_docs))
		return ;
	if (command->type == SUBSHELL)
		return (run_subshell(command, env_variables, here_docs));
	return (run_command(command, get_envp(env_variables)));
}

static void	run_subshell(t_token *command, t_hashmap env_variables,
				t_list *here_docs)
{
	int	exit_code;

	execute_commands(&command->subshell, env_variables, &here_docs);
	exit_code = *(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE);
	ft_hm_clear(&env_variables, &free);
	exit(exit_code);
}

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
		print_error(command->name, NULL, "is a directory");
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
