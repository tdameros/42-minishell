/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:09 by vfries            #+#    #+#             */
/*   Updated: 2023/01/18 17:12:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

// TODO delete me
static int	is_file_operator_token_tmp(t_token *token)
{
	if (token == NULL || token->type != OPERATOR)
		return (0);
	return (token->operator == INPUT_REDIRECT
		|| token->operator == OUTPUT_REDIRECT
		|| token->operator == HERE_DOC
		|| token->operator == APPEND);
}

bool	add_command(t_list **parsed_tokens, t_list **tokens);
//!

t_list	*simplify_tokens(t_list *tokens)
{
	t_list	*parsed_tokens;

	parsed_tokens = NULL;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == OPERATOR
			&& is_file_operator_token_tmp(tokens->content) == 0)
			ft_lst_push(&parsed_tokens, &tokens);
		else if (add_command(&parsed_tokens, &tokens))
		{
			ft_lstclear(&tokens, &free_token);
			ft_lstclear(&parsed_tokens, &free_token);
			return (NULL);
		}
	}
	return (ft_lst_reverse(&parsed_tokens));
}
