/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:09 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 04:33:03 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "parser.h"

void	simplify_tokens(t_list **tokens, t_hashmap env_variables)
{
	t_list	*parsed_tokens;

	parsed_tokens = NULL;
	while (*tokens != NULL)
	{
		if (((t_token *)(*tokens)->content)->type == OPERATOR
			&& is_file_operator_token((*tokens)->content) == 0)
			ft_lst_push(&parsed_tokens, tokens);
		else if (add_command(&parsed_tokens, tokens, env_variables))
		{
			ft_lstclear(tokens, &free_token);
			ft_lstclear(&parsed_tokens, &free_token);
			return ;
		}
	}
	*tokens = ft_lst_reverse(&parsed_tokens);
}
