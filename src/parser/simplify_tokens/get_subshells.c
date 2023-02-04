/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subshells.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:22 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 23:20:28 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_list	*get_subshell(t_list **tokens);
static t_list	*fix_subshells_files(t_list *tokens);
static bool		next_is_subshell(t_list *tokens);
static void		fix_token_files(t_list *cursor);

t_list	*get_subshells(t_list *tokens)
{
	t_token	*token;
	t_list	*tokens_with_subshells;

	tokens_with_subshells = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			ft_lstadd_front(&tokens_with_subshells, get_subshell(&tokens));
		else
			ft_lst_push(&tokens_with_subshells, &tokens);
	}
	return (fix_subshells_files(tokens_with_subshells));
}

static t_list	*get_subshell(t_list **tokens)
{
	t_list	*subshell;
	t_token	*subshell_token;
	t_token	*token;
	int		parentheses;

	ft_lst_push(&subshell, tokens);
	subshell_token = subshell->content;
	subshell_token->type = SUBSHELL;
	subshell_token->operator = -1;
	parentheses = 1;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		if (parentheses == 0)
			break ;
		ft_lst_push(&subshell_token->subshell, tokens);
	}
	ft_lst_get_next_free_current(tokens, &free_token);
	ft_lst_reverse(&subshell_token->subshell);
	subshell_token->subshell = get_subshells(subshell_token->subshell);
	return (subshell);
}

static t_list	*fix_subshells_files(t_list *tokens)
{
	t_list	*cursor;
	t_token	*token;

	cursor = tokens;
	while (cursor != NULL)
	{
		token = cursor->content;
		if (token->type == COMMAND && next_is_subshell(cursor))
			fix_token_files(cursor);
		cursor = cursor->next;
	}
	return (ft_lst_reverse(&tokens));
}

static bool	next_is_subshell(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL || tokens->next == NULL)
		return (false);
	token = tokens->next->content;
	return (token->type == SUBSHELL);
}

static void	fix_token_files(t_list *cursor)
{
	t_token	*token;
	t_token	*next_token;
	t_list	*next_next;

	token = cursor->content;
	next_token = cursor->next->content;
	token->type = SUBSHELL;
	ft_free_split(token->args);
	token->args = NULL;
	token->subshell = next_token->subshell;
	next_token->subshell = NULL;
	next_next = cursor->next->next;
	ft_lstdelone(cursor->next, &free_token);
	cursor->next = next_next;
}
