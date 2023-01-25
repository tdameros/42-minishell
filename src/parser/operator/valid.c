/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:13:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/23 16:13:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	is_separator_operator(t_token *token);
static bool	is_valid_separator_operator(t_list *tokens, enum e_operators *error);
static bool	is_valid_parentheses(t_list *tokens, enum e_operators *error);
static bool	is_file_operator(t_token *token);

bool	is_valid_operators(t_list *tokens, enum e_operators *error)
{
	return (is_valid_parentheses(tokens, error) && is_valid_separator_operator(tokens, error));
}

static bool	is_valid_parentheses(t_list *tokens, enum e_operators *error)
{
	int		open_parentheses;
	int		close_parentheses;
	t_token	*token;

	open_parentheses = 0;
	close_parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			open_parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			close_parentheses++;
		if (close_parentheses > open_parentheses)
		{
			*error = CLOSE_PARENTHESES;
			return (false);
		}
		tokens = tokens->next;
	}
	if (open_parentheses > close_parentheses)
		*error = OPEN_PARENTHESES;
	if (open_parentheses < close_parentheses)
		*error = CLOSE_PARENTHESES;
	return (open_parentheses == close_parentheses);
}

static bool	is_valid_separator_operator(t_list *tokens, enum e_operators *error)
{
	t_token	*current_token;
	t_token	*next_token;

	while (tokens != NULL)
	{
		current_token = tokens->content;
		if (tokens->next != NULL)
			next_token = tokens->next->content;
		else
			next_token = NULL;
		if (is_separator_operator(current_token) && next_token == NULL)
		{
			*error = current_token->operator;
			return (false);
		}
		if (is_file_operator(current_token) && next_token->type != PATH_FILE)
		{
			*error = current_token->operator;
			return (false);
		}
		if (!is_separator_operator(current_token) && next_token != NULL &&(next_token->operator == OPEN_PARENTHESES ))
		{
			ft_printf("%d\n", current_token->operator);
			*error = next_token->operator;
			return (false);
		}
		if (current_token->operator == OPEN_PARENTHESES && next_token->operator == CLOSE_PARENTHESES)
		{
			ft_printf("Here");
			*error = current_token->operator;
			return (false);
		}
//		ft_printf("\n%d\n", current_token->operator);
//		if (current_token->operator == 3)
//			ft_printf("%d\n", next_token->type != COMMAND && next_token->type != OPERATOR && next_token->operator != OPEN_PARENTHESES);
		if (is_separator_operator(current_token) && !is_file_operator(current_token) && (next_token->type != COMMAND && next_token->operator != OPEN_PARENTHESES))
		{
			*error = current_token->operator;
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

static bool	is_separator_operator(t_token *token)
{
	if (token->type != OPERATOR)
		return (false);
	return (token->operator != OPEN_PARENTHESES
		&& token->operator != CLOSE_PARENTHESES);
}

static bool	is_file_operator(t_token *token)
{
	if (token->type != OPERATOR)
		return (false);
	return (token->operator == HERE_DOC
	|| token->operator == APPEND
	|| token->operator == INPUT_REDIRECT
	|| token->operator == OUTPUT_REDIRECT);
}