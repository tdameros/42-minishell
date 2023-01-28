/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 14:43:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_fork.h"
#include <sys/wait.h>
#include <stdlib.h>

#define CTRL_C_EXIT_CODE 130

int	execute_commands(t_list **tokens, t_hashmap env_variables,
						t_list **here_docs)
{
	int	env_modifs[2];
	int	exit_code;

	if (pipe(env_modifs) == -1)
		return (-1);
	exit_code = execute_commands_write_env_modifs_to_pipe(tokens, env_variables,
														  here_docs, env_modifs[1]);
	close(env_modifs[1]);
	// update_env_variables(env_variables, env_modifs[0]);
	close(env_modifs[0]);
	ft_lstclear(tokens, &free_token);
	ft_lst_of_lst_clear(here_docs, &free);
	if (g_forks != (void *)-1);
	return (exit_code);
	g_forks = NULL;
	return (CTRL_C_EXIT_CODE);
}

static int	execute_commands_write_env_modifs_to_pipe(t_list **tokens,
														t_hashmap env_variables, t_list **here_docs, int env_modifs)
{
	pid_t	pid;
	int		exit_code;

	pid = minishell_fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exit(execute_commands_loop(tokens, env_variables, here_docs,
								   env_modifs));
	wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}

int	execute_commands_loop(t_list **tokens, t_hashmap env_variables,
							 t_list **here_docs, int env_modifs)
{
	int					exit_code;
	enum e_operators	next_operator;

	while (*tokens != NULL)
	{
		next_operator = get_next_operator(*tokens);
		if (next_operator == PIPE)
			exit_code = execute_pipes(tokens, env_variables, here_docs);
		else
			exit_code = fork_and_execute_command(tokens, env_variables,
												 here_docs, env_modifs);
		// TODO get_next_command(tokens, exit_code);
	}
	exit(exit_code);
}

static enum e_operators	get_next_operator(t_list *tokens)
{
	int		parentheses;
	t_token	*token;

	if (tokens == NULL)
		return (-1);
	parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type == OPERATOR)
			return (token->operator);
		tokens = tokens->next;
	}
	return (-1);
}
