/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:26:20 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 18:26:21 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static bool	is_quote(t_list *token);

int	add_empty_word_beetween_quotes(t_list **tokens)
{
	t_list		*tmp_node;
	t_list		*token;
	char		*word;
	int			return_code;

	token = *tokens;
	while (token != NULL)
	{
		if (is_quote(token) && is_quote(token->next))
		{
			word = ft_strdup("");
			if (word == NULL)
				return (-1);
			tmp_node = token->next;
			token->next = NULL;
			return_code = add_back_expansion_node(word, WORD, &token);
			ft_lstadd_back(&token, tmp_node);
			if (return_code < 0)
				return (free(word), -1);
		}
		token = token->next;
	}
	return (0);
}

static bool	is_quote(t_list *token)
{
	t_expansion	*expansion;

	if (token == NULL)
		return (false);
	expansion = token->content;
	if (expansion == NULL)
		return (false);
	return (expansion->type == DOUBLE_QUOTE || expansion->type == SIMPLE_QUOTE);
}
