/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:45:10 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 22:00:40 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "exit_code.h"

static bool	first_token_is_bad(t_list *token);

bool	parse_tokens(t_list	**tokens, t_hashmap env_variables)
{
	if (first_token_is_bad(*tokens))
	{
		print_syntax_error(*tokens);
		exit_code(2);
		return (true);
	}
	if (simplify_tokens(tokens, env_variables))
		return (true);
	if (is_syntax_ok(*tokens) == false)
		return (true);
	return (false);
}

static bool	first_token_is_bad(t_list *token)
{
	return (syntax_is_operator(token)
		&& is_file_operator_token(token->content) == false);
}
