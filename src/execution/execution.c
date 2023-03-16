/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:03:22 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:32:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>

#include "terminal.h"
#include "exit_code.h"
#include "execution.h"
#include "minishell_signal.h"

static void				execute_commands_loop(t_minishell *minishell);
static enum e_operators	get_next_operator(t_list *tokens);
static void				get_next_command(t_list **tokens, int last_exit_code);
static void				skip_to_next_command(t_list **tokens,
							enum e_operators target);

void	execute_commands(t_minishell *minishell)
{
	if (terminal_restore(minishell->termios_save) < 0)
	{
		ft_lstclear(&minishell->tokens, &free_token);
		ft_lst_of_lst_clear(&minishell->here_docs, &free);
		set_exit_code(-1);
		return ;
	}
	if (signal_init_handling_inside_execution() < 0)
	{
		ft_lstclear(&minishell->tokens, &free_token);
		ft_lst_of_lst_clear(&minishell->here_docs, &free);
		terminal_disable_ctrl_backslash_output();
		set_exit_code(-1);
		return ;
	}
	execute_commands_loop(minishell);
	ft_lstclear(&minishell->tokens, &free_token);
	ft_lst_of_lst_clear(&minishell->here_docs, &free);
	if (signal_init_handling_outside_execution() < 0)
		set_exit_code(-1);
	if (terminal_disable_ctrl_backslash_output() < 0)
		set_exit_code(-1);
	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
}

static void	execute_commands_loop(t_minishell *minishell)
{
	if (minishell == NULL)
		return ;
	while (minishell->tokens != NULL)
	{
		if (get_next_operator(minishell->tokens) == PIPE)
			execute_pipes(minishell);
		else
			execute_command_no_pipe(minishell, false);
		if (get_exit_code() == -1)
			return ;
		if (minishell->tokens != NULL)
			get_next_command(&minishell->tokens, get_exit_code());
	}
}

static enum e_operators	get_next_operator(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL || tokens->next == NULL || tokens->next->content == NULL)
		return (-1);
	token = tokens->next->content;
	return (token->operator);
}

static void	get_next_command(t_list **tokens, int last_exit_code)
{
	t_token	*token;

	if (tokens == NULL || *tokens == NULL || (*tokens)->content == NULL)
		return ;
	token = (*tokens)->content;
	if (token->operator == OR && last_exit_code != 0)
		ft_lst_get_next_free_current(tokens, &free_token);
	else if (token->operator == OR)
		skip_to_next_command(tokens, AND);
	else if (token->operator == AND && last_exit_code == 0)
		ft_lst_get_next_free_current(tokens, &free_token);
	else
		skip_to_next_command(tokens, OR);
}

static void	skip_to_next_command(t_list **tokens, enum e_operators target)
{
	t_token	*token;

	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token && token->operator == target)
		{
			ft_lst_get_next_free_current(tokens, &free_token);
			return ;
		}
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}
