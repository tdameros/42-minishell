/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:58:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/25 13:58:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_one_command(t_list **tokens);
static void	get_command_following_or(t_list **tokens);
static void	get_next_command(t_list **tokens);

void	get_next_command_to_run(t_list **tokens, enum e_operators operator,
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

	if (*tokens == NULL)
		return ;
	token = (*tokens)->content;
	if (token->operator != OPEN_PARENTHESES)
		ft_lst_get_next_free_current(tokens, &free_token);
	commands_skipped = 0;
	parentheses = 0;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type != OPERATOR)
			commands_skipped++;
		if (commands_skipped > 1 && parentheses == 0 && token->type != OPERATOR)
			return ;
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}

static void	get_command_following_or(t_list **tokens)
{
	int		parentheses;
	t_token	*token;
	int		or_found;

	or_found = 0;
	parentheses = 0;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->operator == OR)
			or_found++;
		else if (or_found > 0 && parentheses == 0 && token->type != OPERATOR)
			return ;
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}

static void	get_next_command(t_list **tokens)
{
	int		parentheses;
	t_token	*token;

	if (*tokens == NULL)
		return ;
	token = (*tokens)->content;
	if (token->operator != OPEN_PARENTHESES)
		ft_lst_get_next_free_current(tokens, &free_token);
	parentheses = 0;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type != OPERATOR)
			return ;
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}
