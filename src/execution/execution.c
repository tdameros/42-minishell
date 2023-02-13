/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/12 19:24:54 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include "minishell_signal.h"
#include "expansions.h"
#include "exit_code.h"
#include <sys/wait.h>
#include <stdlib.h>

static void		execute_commands_loop(t_list **tokens, t_hashmap env_variables,
					t_list **here_docs);
static int		execute_command_no_pipe_builtin(t_list *command,
					t_hashmap env_variables, t_list **here_docs);
static pid_t	fork_and_execute_command(t_token *command,
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
	while (*tokens != NULL)
	{
		if (get_next_operator(*tokens) == PIPE)
			execute_pipes(tokens, env_variables, here_docs);
		else
			execute_command_no_pipe(tokens, env_variables, here_docs);
		if (*tokens != NULL)
			get_next_command(tokens, exit_code(GET));
	}
}

int	execute_command_no_pipe(t_list **tokens, t_hashmap env_variables,
		t_list **here_docs)
{
	int		tmp_exit_code;
	t_list	*command;
	t_token	*command_token;
	pid_t	pid;

	command = NULL;
	ft_lst_push(&command, tokens);
	command_token = command->content;
	if (command_token->type != SUBSHELL
		&& apply_token_expansion(command_token, *here_docs, env_variables) < 0)
		return (print_error(command_token->name, NULL, get_error()), -1);
	if (command_token->type == BUILTIN)
		return (execute_command_no_pipe_builtin(command, env_variables,
				here_docs));
	pid = fork_and_execute_command(command->content, env_variables,
			*here_docs);
	skip_token_here_docs(command, here_docs);
	ft_lstclear(&command, &free_token);
	if (pid == -1)
		return (exit_code(-1));
	waitpid(pid, &tmp_exit_code, 0);
	return (get_pid_exit_code(tmp_exit_code));
}

static int	execute_command_no_pipe_builtin(t_list *command,
				t_hashmap env_variables, t_list **here_docs)
{
	execute_command(command->content, env_variables, *here_docs);
	skip_token_here_docs(command, here_docs);
	ft_lstclear(&command, &free_token);
	return (exit_code(GET));
}

static pid_t	fork_and_execute_command(t_token *command,
					t_hashmap env_variables, t_list *here_docs)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error(command->args[0], FORK_FAILED, get_error());
		return (-1);
	}
	if (pid != 0)
		return (pid);
	execute_command(command, env_variables, here_docs);
	exit(exit_code(GET));
}
