/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/30 02:26:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "minishell_fork.h"
#include "built_in.h"
#include "env_variables.h"
#include "execution.h"
#include <sys/wait.h>
#include <stdlib.h>

#define CTRL_C_EXIT_CODE 130

static void				execute_commands_loop(t_list **tokens,
							t_hashmap env_variables, t_list **here_docs);
static pid_t			fork_and_execute_command(t_token *command,
							t_hashmap env_variables, t_list *here_docs);

void	execute_commands(t_list **tokens, t_hashmap env_variables,
			t_list **here_docs)
{
	execute_commands_loop(tokens, env_variables, here_docs);
	ft_lstclear(tokens, &free_token);
	ft_lst_of_lst_clear(here_docs, &free);
}

static void	execute_commands_loop(t_list **tokens, t_hashmap env_variables,
				t_list **here_docs)
{
	int	exit_code;

	while (*tokens != NULL)
	{
		if (get_next_operator(*tokens) == PIPE)
			exit_code = execute_pipes(tokens, env_variables, here_docs);
		else
			exit_code = execute_command_no_pipe(tokens, env_variables,
					here_docs);
		update_last_exit_code(env_variables, exit_code);
		if (*tokens != NULL)
			get_next_command(tokens, exit_code);
	}
}

int	execute_command_no_pipe(t_list **tokens, t_hashmap env_variables,
		t_list **here_docs)
{
	int		exit_code;
	t_list	*command;
	t_token	*command_token;
	pid_t	pid;

	command = NULL;
	ft_lst_push(&command, tokens);
	command_token = command->content;
	if (command_token->type == BUILTIN)
	{
		execute_command(command->content, env_variables, *here_docs);
		skip_token_here_docs(command, here_docs);
		ft_lstclear(&command, &free_token);
		return (ft_atoi(ft_hm_get_content(env_variables, LAST_EXIT_CODE)));
	}
	pid = fork_and_execute_command(command->content, env_variables,
			*here_docs);
	skip_token_here_docs(command, here_docs);
	ft_lstclear(&command, &free_token);
	if (pid == -1)
		return (-1);
	waitpid(pid, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}

static pid_t	fork_and_execute_command(t_token *command,
					t_hashmap env_variables, t_list *here_docs)
{
	pid_t	pid;

	pid = minishell_fork();
	if (pid == -1)
	{
		print_error(command->args[0], FORK_FAILED, get_error());
		return (-1);
	}
	if (pid != 0)
		return (pid);
	execute_command(command, env_variables, here_docs);
	exit(ft_atoi(ft_hm_get_content(env_variables, LAST_EXIT_CODE)));
}
