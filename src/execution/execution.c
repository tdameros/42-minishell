/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/29 00:29:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "minishell_fork.h"
#include "env_variables.h"
#include "execution.h"
#include <sys/wait.h>
#include <stdlib.h>

#define CTRL_C_EXIT_CODE 130

static void				execute_commands_loop(t_list **tokens,
							t_hashmap env_variables, t_list **here_docs,
							int *exit_code);
static int				execute_command_no_pipe(t_list **tokens,
							t_hashmap env_variables, t_list **here_docs);
static int				fork_and_execute_command(t_token *command,
							t_hashmap env_variables, t_list *here_docs);

void	execute_commands(t_list **tokens, t_hashmap env_variables,
			t_list **here_docs)
{
	int	*exit_code;

	exit_code = ft_hm_get_content(env_variables, LAST_EXIT_CODE);
	execute_commands_loop(tokens, env_variables, here_docs, exit_code);
	ft_lstclear(tokens, &free_token);
	ft_lst_of_lst_clear(here_docs, &free);
}

static void	execute_commands_loop(t_list **tokens, t_hashmap env_variables,
				t_list **here_docs, int *exit_code)
{
	while (*tokens != NULL)
	{
		if (get_next_operator(*tokens) == PIPE)
			*exit_code = execute_pipes(tokens, env_variables, here_docs);
		else
			*exit_code = execute_command_no_pipe(tokens, env_variables,
					here_docs);
		if (*tokens != NULL)
			get_next_command(tokens, *exit_code);
	}
}

static int	execute_command_no_pipe(t_list **tokens, t_hashmap env_variables,
				t_list **here_docs)
{
	int		exit_code;
	t_list	*command;
	t_token	*command_token;

	command = NULL;
	ft_lst_push(&command, tokens);
	command_token = command->content;
	if (command_token->type == BUILTIN)
	{
		execute_command(command->content, env_variables, *here_docs);
		// TODO skip here_docs
		ft_lstclear(&command, &free_token);
		return (*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE));
	}
	exit_code = fork_and_execute_command(command->content, env_variables,
			*here_docs);
	// TODO skip here_docs
	ft_lstclear(&command, &free_token);
	if (exit_code)
		return (exit_code);
	wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}

static int	fork_and_execute_command(t_token *command, t_hashmap env_variables,
				t_list *here_docs)
{
	pid_t	pid;

	pid = minishell_fork();
	if (pid == -1)
	{
		print_error(command->args[0], FORK_FAILED, get_error());
		return (-1);
	}
	if (pid != 0)
		return (0);
	execute_command(command, env_variables, here_docs);
	exit(*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE));
}
