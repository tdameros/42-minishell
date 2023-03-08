/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:25:42 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 18:25:45 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static int		join_next_words(t_list **tokens, t_list **new_list);
static char		*join_words(t_list *token);
static t_list	*skip_word_expansion(t_list *tokens);

int	merge_words(t_list **tokens)
{
	t_expansion	*expansion;
	t_list		*token;
	t_list		*new_list;

	token = *tokens;
	new_list = NULL;
	while (token != NULL)
	{
		expansion = token->content;
		if (expansion->type == WORD)
		{
			if (join_next_words(&token, &new_list) < 0)
				return (ft_lstclear(&new_list, free_expansion), -1);
			token = skip_word_expansion(token);
		}
		else
		{
			if (add_front_expansion_node(NULL, expansion->type, &new_list) < 0)
				return (ft_lstclear(&new_list, free_expansion), -1);
			token = token->next;
		}
	}
	ft_lstclear(tokens, free_expansion);
	ft_lst_reverse(&new_list);
	*tokens = new_list;
	return (0);
}

static int	join_next_words(t_list **tokens, t_list **new_list)
{
	char		*new_word;

	new_word = join_words(*tokens);
	if (new_word == NULL)
		return (-1);
	if (add_front_expansion_node(new_word, WORD, new_list) < 0)
	{
		free(new_word);
		return (-1);
	}
	return (0);
}

static char	*join_words(t_list *token)
{
	t_expansion	*expansion;
	char		*new_word;
	char		*temp;

	expansion = token->content;
	new_word = ft_strdup(expansion->content);
	if (new_word == NULL)
		return (NULL);
	token = token->next;
	while (token != NULL && ((t_expansion *) token->content)->type == WORD)
	{
		expansion = token->content;
		temp = ft_strjoin(new_word, expansion->content);
		free(new_word);
		if (temp == NULL)
			return (NULL);
		new_word = temp;
		token = token->next;
	}
	return (new_word);
}

static t_list	*skip_word_expansion(t_list *tokens)
{
	t_expansion	*expansion;

	expansion = tokens->content;
	while (expansion->type == WORD)
	{
		tokens = tokens->next;
		if (tokens == NULL)
			return (tokens);
		expansion = tokens->content;
	}
	return (tokens);
}
