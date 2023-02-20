/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_no_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:13:15 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 21:35:07 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "expansions.h"
#include "minishell_struct.h"
#include "error.h"
#include "execution.h"
#include "exit_code.h"
#include "sys/wait.h"
#include "env_variables.h"

static void		execute_builtin_no_pipe(t_minishell *minishell, t_list **tokens,
					t_token *token);
static void		skip_command(t_minishell *minishell, t_list **tokens);
static void		execute_non_builtin_no_pipe(t_minishell *minishell,
					t_list **tokens, t_token *token,
					bool is_last_piped_command);
static pid_t	fork_and_execute_command(t_minishell *minishell,
					t_list **tokens, t_token *command);

void	execute_command_no_pipe(t_minishell *minishell, t_list **tokens,
			bool is_last_piped_command)
{
	t_token	*token;

	if (minishell == NULL || tokens == NULL || *tokens == NULL
		|| (*tokens)->content == NULL)
		return ;
	token = (*tokens)->content;
	if (apply_token_expansion(
			token, minishell->here_docs, minishell->env_variables) < 0)
	{
		exit_code(-1);
		print_error(token->name, NULL, get_error());
		return ;
	}
	if (token->type == BUILTIN)
		return (execute_builtin_no_pipe(minishell, tokens, token));
	execute_non_builtin_no_pipe(minishell, tokens, token,
		is_last_piped_command);
}

static void	execute_builtin_no_pipe(t_minishell *minishell, t_list **tokens,
				t_token *token)
{
	if (minishell == NULL)
		return ;
	execute_command(minishell, tokens, token, NULL);
	skip_token_here_docs(token, &minishell->here_docs);
	skip_command(minishell, tokens);
}

static void	skip_command(t_minishell *minishell, t_list **tokens)
{
	if (minishell == NULL || tokens == NULL)
		return ;
	if (minishell->tokens == *tokens)
		ft_lst_get_next_free_current(&minishell->tokens, &free_token);
	else
		ft_lst_get_next_free_current(tokens, &free_token);
}

static void	execute_non_builtin_no_pipe(t_minishell *minishell, t_list **tokens,
				t_token *token, bool is_last_piped_command)
{
	pid_t	pid;
	int		status;

	pid = fork_and_execute_command(minishell, tokens, token);
	skip_token_here_docs(token, &minishell->here_docs);
	skip_command(minishell, tokens);
	if (pid == -1)
		exit_code(-1);
	else if ((is_last_piped_command == false && waitpid(pid, &status, 0) >= 0)
		|| (waitpid(pid, &status, 0) >= 0 && WIFSIGNALED(status) == false))
		exit_code(WEXITSTATUS(status));
}

static pid_t	fork_and_execute_command(t_minishell *minishell,
					t_list **tokens, t_token *command)
{
	pid_t	pid;
	char	**envp;

	if (command->type != SUBSHELL)
		envp = get_non_empty_envp(minishell->env_variables, command->args[0]);
	else
		envp = NULL;
	pid = fork();
	if (pid == -1)
	{
		ft_free_split(envp);
		print_error(command->args[0], FORK_FAILED, get_error());
		return (-1);
	}
	if (pid != 0)
	{
		ft_free_split(envp);
		return (pid);
	}
	execute_command(minishell, tokens, command, envp);
	ft_free_split(envp);
	// TODO free minishell
	exit(exit_code(GET));
}
