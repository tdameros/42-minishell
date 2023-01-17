/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:09 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 14:05:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdbool.h>

// TODO delete me
void	add_command(t_list **parsed_tokens, t_list **tokens);
//!

t_list	*simplify_tokens(t_list *tokens)
{
	t_list	*parsed_tokens;

	parsed_tokens = NULL;
	while (tokens != NULL)
	{
		ft_printf("simplify_tokens(): %p\n", tokens);

		if (((t_token *)tokens->content)->type == OPERATOR)
			ft_lst_push(&parsed_tokens, &tokens);
		else
			add_command(&parsed_tokens, &tokens);
	}
	return (ft_lst_reverse(&parsed_tokens));
}
