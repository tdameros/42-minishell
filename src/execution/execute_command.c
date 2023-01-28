/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:31:41 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 18:16:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "built_in.h"
#include "execution.h"
#include "minishell_fork.h"

static void	run_builtin(t_token *command, t_hashmap env_variables);
static void	run_subshell(t_token *command, t_hashmap env_variables,
				t_list *here_docs);
static void	run_command(t_token *command, char **envp);

void	execute_command(t_token *command, t_hashmap env_variables,
			t_list *here_docs)
{
	int	files_status;

	// TODO fix_token_variables()
	//files_status = open_and_dup_files(command->files, env_variables, here_docs);
	files_status = 0;
	if (files_status != 0)
		return ;
	if (command->type == BUILTIN)
		return (run_builtin(command, env_variables));
	if (command->type == SUBSHELL)
		return (run_subshell(command, env_variables, here_docs));
	return (run_command(command, get_envp(env_variables)));
}

static void	run_builtin(t_token *command, t_hashmap env_variables)
{
	// int	old_std_io[2];

	// dup2(STDIN_FILENO, old_std_io[0]); // TODO Secure dups
	// dup2(STDOUT_FILENO, old_std_io[1]);
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
	// dup2(old_std_io[0], STDIN_FILENO);	// TODO Secure dups
	// dup2(old_std_io[1], STDOUT_FILENO);
	if (command->builtin == EXIT)
		exit_builtin(command->args, env_variables);
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
	print_error(command->args[0], NULL, get_error());
	ft_free_split(envp);
	exit(-1);
}
