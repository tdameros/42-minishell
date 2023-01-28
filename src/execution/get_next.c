/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:24:04 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 16:54:45 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_to_next_command(t_list **tokens, enum e_operators target);

enum e_operators	get_next_operator(t_list *tokens)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == OPERATOR)
			return (token->operator);
		tokens = tokens->next;
	}
	return (-1);
}

void	get_next_command(t_list **tokens, int exit_code)
{
	t_token	*token;

	if (*tokens == NULL)
		return ;
	token = (*tokens)->content;
	if (token->operator == OR && exit_code != 0)
		ft_lst_get_next_free_current(tokens, &free_token);
	else if (token->operator == OR)
	{
		ft_lst_get_next_free_current(tokens, &free_token);
		ft_lst_get_next_free_current(tokens, &free_token);
		skip_to_next_command(tokens, AND);
	}
	else if (token->operator == AND && exit_code == 0)
		ft_lst_get_next_free_current(tokens, &free_token);
	else
	{
		ft_lst_get_next_free_current(tokens, &free_token);
		ft_lst_get_next_free_current(tokens, &free_token);
		skip_to_next_command(tokens, OR);
	}
}

static void	skip_to_next_command(t_list **tokens, enum e_operators target)
{
	t_token	*token;

	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->operator == target)
		{
			ft_lst_get_next_free_current(tokens, &free_token);
			return ;
		}
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}
