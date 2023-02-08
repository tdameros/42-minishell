/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:04:18 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 21:59:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "lexer.h"
#include "error.h"

bool	syntax_is_operator(t_list *token_lst)
{
	t_token	*token;

	if (token_lst == NULL || token_lst->content == NULL)
		return (false);
	token = token_lst->content;
	if (token->type == OPERATOR)
		return (true);
	return (false);
}

bool	syntax_is_empty(t_list *token_lst)
{
	return (token_lst == NULL || token_lst->content == NULL);
}

enum e_operators	syntax_get_operator(t_list *token_lst)
{
	t_token	*token;

	if (token_lst == NULL || token_lst->content == NULL)
		return (-1);
	token = token_lst->content;
	return (token->operator);
}

void	print_syntax_error(t_list *token)
{
	const enum e_operators	error = syntax_get_operator(token);

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
	else
		print_error(NULL, NULL, "syntax error near unexpected token `newline'");
}
