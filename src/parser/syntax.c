/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:48:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/09 01:51:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"

static bool	is_valid_operator_syntax(t_token *token, t_token *previous_token);
static bool	is_separator_token(t_token *token);
static bool	is_redirect_token(t_token *token);
static void	print_syntax_error(t_token *token);

int	parse_syntax(t_list *tokens)
{
	size_t	open_parentheses;
	size_t	close_parentheses;
	t_token	*token;
	t_token	*prev_token;

	open_parentheses = 0;
	close_parentheses = 0;
	prev_token = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (is_valid_operator_syntax(token, prev_token) == false)
			return (print_syntax_error(token), -1);
		open_parentheses += token->operator == OPEN_PARENTHESES;
		close_parentheses += token->operator == CLOSE_PARENTHESES;
		if (close_parentheses > open_parentheses)
			return (print_syntax_error(token), -1);
		prev_token = token;
		tokens = tokens->next;
	}
	if (prev_token->operator == OPEN_PARENTHESES || is_separator_token(token))
		return (0);
	if (is_redirect_token(prev_token))
		return (print_syntax_error(NULL), -1);
	return (open_parentheses == close_parentheses);
}

static bool	is_valid_operator_syntax(t_token *token, t_token *previous_token)
{
	if (previous_token != NULL && previous_token->operator == HERE_DOC
		&& token->type == OPERATOR)
		return (false);
	if (previous_token != NULL && token->operator == OPEN_PARENTHESES
		&& (!is_separator_token(previous_token)
			&& previous_token->operator != OPEN_PARENTHESES))
		return (false);
	if (token->operator == CLOSE_PARENTHESES && previous_token != NULL
		&& previous_token->type == OPERATOR
		&& previous_token->operator != CLOSE_PARENTHESES)
		return (false);
	if (token->type == OPERATOR && previous_token == NULL)
		return (!is_separator_token(token));
	if (is_redirect_token(token) && is_redirect_token(previous_token))
		return (false);
	if (is_separator_token(token) && previous_token->type == OPERATOR
		&& previous_token->operator != CLOSE_PARENTHESES)
		return (false);
	return (true);
}

static bool	is_separator_token(t_token *token)
{
	if (token->type != OPERATOR)
		return (false);
	return (token->operator == OR
		|| token->operator == AND
		|| token->operator == PIPE);
}

static bool	is_redirect_token(t_token *token)
{
	if (token->type != OPERATOR)
		return (false);
	return (token->operator == INPUT_REDIRECT
		|| token->operator == OUTPUT_REDIRECT
		|| token->operator == HERE_DOC
		|| token->operator == APPEND);
}

static void	print_syntax_error(t_token *token)
{
	enum e_operators	error;

	if (token == NULL)
		return (print_error(NULL, NULL,
				"syntax error near unexpected token `newline'"));
	error = token->operator;
	if (error == OPEN_PARENTHESES)
		print_error(NULL, NULL, "syntax error near unexpected token `('");
	else if (error == CLOSE_PARENTHESES)
		print_error(NULL, NULL, "syntax error near unexpected token `)'");
	else if (error == OR)
		print_error(NULL, NULL, "syntax error near unexpected token `||'");
	else if (error == AND)
		print_error(NULL, NULL, "syntax error near unexpected token `&&'");
	else if (error == PIPE)
		print_error(NULL, NULL, "syntax error near unexpected token `|'");
	else if (error == INPUT_REDIRECT)
		print_error(NULL, NULL, "syntax error near unexpected token `<'");
	else if (error == OUTPUT_REDIRECT)
		print_error(NULL, NULL, "syntax error near unexpected token `>'");
	else if (error == HERE_DOC)
		print_error(NULL, NULL, "syntax error near unexpected token `<<'");
	else if (error == APPEND)
		print_error(NULL, NULL, "syntax error near unexpected token `>>'");
}
