/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:31:42 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 19:31:43 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static char	*next_wildcard(char *content, bool is_quoted);
static int	search_in_word(char *content, bool is_quoted, t_list **new_list);
static int	add_wildcard(char *next_wildcard, t_list **new_list);

t_list	*wildcards_lexer(t_list *expansions_tokens)
{
	int			quote;
	t_expansion	*expansion;
	t_list		*new_list;

	quote = -1;
	new_list = NULL;
	while (expansions_tokens != NULL)
	{
		expansion = expansions_tokens->content;
		if (quote == -1 && (expansion->type == DOUBLE_QUOTE
				|| expansion->type == SIMPLE_QUOTE))
			quote = expansion->type;
		else if (quote == (int) expansion->type)
			quote = -1;
		if (search_in_word(expansion->content, quote != -1, &new_list) < 0)
			return (ft_lstclear(&new_list, free_expansion), NULL);
		expansions_tokens = expansions_tokens->next;
	}
	return (new_list);
}

static int	search_in_word(char *content, bool is_quoted, t_list **new_list)
{
	char	*wildcard;
	char	*new_word;

	while (content != NULL && *content != '\0')
	{
		wildcard = next_wildcard(content, is_quoted);
		if (wildcard == NULL)
			new_word = ft_strdup(content);
		else
			new_word = ft_substr(content, 0, wildcard - content);
		if (ft_strlen(new_word) > 0)
		{
			if (add_back_expansion_node(new_word, WORD, new_list) < 0)
				return (free(new_word), -1);
		}
		else
			free(new_word);
		if (add_wildcard(wildcard, new_list) < 0)
			return (-1);
		if (wildcard != NULL)
			content = wildcard + 1;
		else
			content = wildcard;
	}
	return (0);
}

static int	add_wildcard(char *next_wildcard, t_list **new_list)
{
	if (next_wildcard != NULL && *next_wildcard == '/')
	{
		if (add_back_expansion_node(NULL, SLASH, new_list) < 0)
			return (-1);
	}
	else if (next_wildcard != NULL && *next_wildcard == '*')
	{
		if (add_back_expansion_node(NULL, STAR, new_list) < 0)
			return (-1);
	}
	return (0);
}

static char	*next_wildcard(char *content, bool is_quoted)
{
	char	*slash;
	char	*star;

	slash = ft_strchr(content, '/');
	if (is_quoted == true)
		return (slash);
	star = ft_strchr(content, '*');
	if (slash == NULL)
		return (star);
	if (star == NULL)
		return (slash);
	if (star < slash)
		return (star);
	return (slash);
}
