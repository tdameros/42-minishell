/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:09 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 16:02:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer.h"
#include "parser.h"

static void	free_lsts(t_list **simplified_tokens, t_list **tokens);

int	simplify_tokens(t_list **tokens, t_hashmap env_variables)
{
	t_list	*simplified_tokens;
	t_token	*new_command;
	t_list	*new_node;
	t_token	*token;

	simplified_tokens = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPERATOR && is_file_operator_token(token) == 0)
		{
			ft_lst_push(&simplified_tokens, tokens);
			continue ;
		}
		new_command = get_new_command(tokens, env_variables);
		new_node = ft_lstnew(new_command);
		if (new_command == NULL || new_node == NULL)
		{
			free_lsts(&simplified_tokens, tokens);
			return (-1);
		}
		ft_lstadd_front(&simplified_tokens, new_node);
	}
	*tokens = get_subshells(ft_lst_reverse(&simplified_tokens));
	return (0);
}

static void	free_lsts(t_list **simplified_tokens, t_list **tokens)
{
	ft_lstclear(simplified_tokens, &free_token);
	ft_lstclear(tokens, &free_token);
}
