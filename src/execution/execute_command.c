/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:31:41 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 14:45:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env_variables.h"

void	execute_command(t_list *command, t_hashmap env_variables,
			t_list *here_docs, int env_modifs)
{
	const t_token	*token = command->content;

	if (token->type == BUILTIN)
		return (run_builtin(token, env_variables, here_docs, env_modifs));
	if (token->operator == OPEN_PARENTHESES)
		return (run_subshell(command, env_variables, here_docs));
	return (run_command(token, env_variables, here_docs));
}

static void	run_builtin(t_token *command, t_hashmap env_variables,
			t_list *here_docs, int env_modifs)
{
	(void)command;
	(void)env_variables;
	(void)here_docs;
	(void)env_modifs;
	/*
	int	files_status;

	files_status = open_and_dup_files(command->files, env_variables, here_docs);
	if (files_status)
		exit(files_status);
	if (command->builtin == ECHO)
		// pass
	else if (command->builtin == CD)
		// pass
	else if (command->builtin == PWD)
		// pass
	else if (command->builtin == EXPORT)
		// pass
	else if (command->builtin == UNSET)
		// pass
	else if (command->builtin == ENV)
		// pass
	else if (command->builtin == EXIT)
		// pass
	*/
}

static void	run_subshell(t_list *tokens, t_hashmap env_variables,
			t_list *here_docs)
{
	t_list	*cursor;

	ft_lst_get_next_free_current(&tokens, &free_token);
	while (cursor->next->next != NULL)
		cursor = cursor->next;
	ft_lstdelone(cursor->next, &free_token);
	cursor->next = NULL;
	execute_commands_loop(&tokens, env_variables, &here_docs, -1);
}

static void	run_command(t_token *command, t_hashmap env_variables,
				t_list *here_docs)
{
	char	**envp;
	int		files_status;

	files_status = open_and_dup_files(command->files, env_variables, here_docs);
	if (files_status)
		exit(files_status);
	envp = get_envp(env_variables);
	execve(command->name, command->args, envp);
	ft_free_split(envp);
	exit(-1);
}

static int	open_and_dup_files(t_list *files, t_hashmap env_variables,
			t_list **here_docs)
{
	t_token	*token;

	while (files != NULL)
	{
		token = files->content;
		if (token->operator == INPUT_REDIRECT)
	}
}