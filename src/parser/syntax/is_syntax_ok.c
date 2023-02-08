/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_syntax_ok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:44:58 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 21:59:46 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "lexer.h"
#include "parser.h"
#include "exit_code.h"

static bool	check_token(t_list *token);

/// @brief 	return true if tokens are ok, false if the syntax is off.
/// 		Sets exit_code to 2 when bad syntax.
/// 		(Assumes tokens have passed through simplify_tokens())
/// @param tokens 	Tokens for which to test the syntax,
/// 				they need to have been passed through simplify_tokens()
/// @details 	The files syntax is not checked as this was done
/// 			in simplifiy_tokens()
/// @return 	return true if tokens are ok, false if the syntax is off
bool	is_syntax_ok(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (check_token(tokens))
		{
			exit_code(2);
			return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

static bool	check_token(t_list *tokens)
{
	const t_token	*token = tokens->content;

	if (token->type == SUBSHELL)
		return (is_syntax_ok(token->subshell));
	if (syntax_is_operator(tokens)
		&& (syntax_is_operator(tokens->next) || syntax_is_empty(tokens->next)))
	{
		print_syntax_error(tokens->next);
		return (true);
	}
	return (false);
}
