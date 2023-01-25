/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:54:27 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 21:17:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	execute_commands(t_list *tokens, t_list_i *here_docs)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		exit_code = execute_commands_loop(tokens);
		// TODO free_all
		exit(exit_code);
	}
	wait(&exit_code);
	exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}

static int	execute_commands_loop(t_list *tokens)
{
	t_token 			*token;
	enum e_operators	operator;
	int					last_exit_code;

	while (tokens != NULL)
	{
		operator = get_next_operator(tokens);
		if (operator == PIPE)
			last_exit_code = execute_piped_command();
		else
			last_exit_code = execute_normal_command();
		get_next_command_to_run(&tokens, operator, last_exit_code);
	}
	return (last_exit_code);
}

static enum e_operators	get_next_operator(t_list *tokens)
{
	t_token *token;

	if (tokens == NULL)
		return (-1);
	token = tokens->content;
	while (token->type != OPERATOR || token->operator == OPEN_PARENTHESES
		|| token->operator == CLOSE_PARENTHESES)
	{
		tokens == tokens->next;
		if (tokens == NULL)
			return (-1);
		token = tokens->content;
	}
	return (token->operator);
}

static void	get_next_command_to_run(t_list **tokens, enum e_operators operator,
				int last_exit_code)
{
	if (operator == OR && last_exit_code == 0)
		return (skip_one_command(tokens));
	if (operator == AND && last_exit_code != 0)
		return (get_command_following_or(tokens));
	return (get_next_command(tokens));
}

static void	skip_one_command(t_list **tokens)
{
	int		parentheses;
	t_token	*token;
	int		commands_skipped;

	if (token->operator != OPEN_PARENTHESES)
		ft_lst_get_next_free_current(&tokens, &free_token);
	commands_skipped = 0;
	parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type != OPERATOR)
			commands_skipped++;
		if (commands_skipped > 1 && parentheses == 0 && token->type != OPERATOR)
			return (tokens);
		ft_lst_get_next_free_current(&tokens, &free_token);
	}
}

static void	get_command_following_or(t_list **tokens)
{
	int		parentheses;
	t_token	*token;
	int		or_found;

	or_found = 0;
	parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->operator == OR)
			or_found++;
		else if (or_found > 0 && parentheses == 0 && token->type != OPERATOR)
			return (tokens);
		ft_lst_get_next_free_current(&tokens, &free_token);
	}
}

static void	get_next_command(t_list **tokens)
{
	int		parentheses;
	t_token	*token;

	parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type != OPERATOR)
			return (tokens);
		ft_lst_get_next_free_current(&tokens, &free_token);
	}
}
