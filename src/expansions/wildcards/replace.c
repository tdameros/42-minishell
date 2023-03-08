/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:37:16 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 19:37:16 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

#include "libft.h"

#include "expansions.h"

static t_list	*get_token_before_space(t_list *tokens);
static void		change_token_and_space(t_list **token, t_list **space);
static int		argument_replace_wildcards(t_list **tokens);
static int		add_space_between_wildcards(t_list **match_wildcards);

int	replace_wildcards(t_list **tokens)
{
	t_list	*before_space;
	t_list	*space;
	t_list	*token;
	t_list	*new_list;

	token = *tokens;
	new_list = NULL;
	while (token != NULL)
	{
		before_space = get_token_before_space(token);
		space = before_space->next;
		before_space->next = NULL;
		if (argument_replace_wildcards(&token) < 0)
		{
			*tokens = space;
			ft_lstclear(&token, free_expansion);
			ft_lstclear(&new_list, free_expansion);
			return (-1);
		}
		ft_lstadd_back(&new_list, token);
		change_token_and_space(&token, &space);
		ft_lstadd_back(&new_list, space);
	}
	*tokens = new_list;
	return (0);
}

static t_list	*get_token_before_space(t_list *tokens)
{
	t_expansion	*expansion;

	if (tokens == NULL)
		return (NULL);
	if (tokens->next != NULL)
		expansion = tokens->next->content;
	while (tokens->next != NULL && expansion->type != SPACE)
	{
		tokens = tokens->next;
		if (tokens->next != NULL)
			expansion = tokens->next->content;
	}
	return (tokens);
}

static void	change_token_and_space(t_list **token, t_list **space)
{
	if (*space != NULL)
	{
		*token = (*space)->next;
		(*space)->next = NULL;
	}
	else
		*token = *space;
}

static int	argument_replace_wildcards(t_list **tokens)
{
	t_list	*pattern;
	t_list	*match;

	errno = 0;
	pattern = wildcards_lexer(*tokens);
	if (errno != 0)
		return (-1);
	if (!has_wildcard_in_pattern(pattern))
		return (ft_lstclear(&pattern, free_expansion), 0);
	match = get_wildcards_list(pattern);
	ft_lstclear(&pattern, free_expansion);
	if (errno != 0)
		return (-1);
	if (ft_lstsize(match) > 0)
	{
		if (add_space_between_wildcards(&match) < 0)
			return (ft_lstclear(&match, free_expansion), -1);
		ft_lstclear(tokens, free_expansion);
		ft_lst_reverse(&match);
		*tokens = match;
	}
	else
		ft_lstclear(&match, free_expansion);
	return (0);
}

static int	add_space_between_wildcards(t_list **match_wildcards)
{
	t_list	*match_with_space;
	t_list	*match;

	match_with_space = NULL;
	match = *match_wildcards;
	while (match != NULL)
	{
		*match_wildcards = match->next;
		match->next = NULL;
		ft_lstadd_front(&match_with_space, match);
		if (add_front_expansion_node(NULL, SPACE, &match_with_space) < 0)
		{
			ft_lstclear(&match_with_space, free_expansion);
			return (-1);
		}
		match = *match_wildcards;
	}
	*match_wildcards = match_with_space;
	return (0);
}
