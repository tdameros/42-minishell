/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:47:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 23:47:57 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static int	add_new_expansion_token(t_expansion *expansion,
				bool is_quoted, t_list **new_list);
static int	add_new_expansion_word(t_expansion *expansion, t_list **new_list);
static int	split_word_expansion(t_expansion *expansion, t_list **new_list);
static void	free_no_used_words(char **words, char **not_used_words);

int	split_words(t_list **tokens)
{
	t_list		*new_list;
	t_list		*token;
	t_expansion	*expansion;
	int			quote;

	quote = -1;
	token = *tokens;
	new_list = NULL;
	while (token != NULL)
	{
		expansion = token->content;
		if ((int) expansion->type == quote)
			quote = -1;
		else if (quote == -1 && (expansion->type == SIMPLE_QUOTE
				|| expansion->type == DOUBLE_QUOTE))
			quote = expansion->type;
		if (add_new_expansion_token(expansion, quote != -1, &new_list) < 0)
			return (ft_lstclear(&new_list, free_expansion), -1);
		token = token->next;
	}
	ft_lstclear(tokens, free_expansion);
	*tokens = new_list;
	return (0);
}

static int	add_new_expansion_token(t_expansion *expansion,
		bool is_quoted, t_list **new_list)
{
	int	return_code;

	if (expansion->type == WORD && is_quoted)
		return_code = add_new_expansion_word(expansion, new_list);
	else if (expansion->type == WORD)
		return_code = split_word_expansion(expansion, new_list);
	else
		return_code = add_back_expansion_node(NULL, expansion->type, new_list);
	return (return_code);
}

static int	add_new_expansion_word(t_expansion *expansion, t_list **new_list)
{
	char	*new_word;

	new_word = ft_strdup(expansion->content);
	if (new_word == NULL)
		return (-1);
	if (add_back_expansion_node(new_word, WORD, new_list) < 0)
	{
		free(new_word);
		return (-1);
	}
	return (0);
}

static int	split_word_expansion(t_expansion *expansion, t_list **new_list)
{
	char		**new_words;
	size_t		index;

	new_words = ft_split(expansion->content, ' ');
	if (new_words == NULL)
		return (-1);
	if (ft_split_size(new_words) <= 1)
	{
		ft_free_split(new_words);
		return (add_new_expansion_word(expansion, new_list));
	}
	index = 0;
	while (new_words[index] != NULL)
	{
		if (add_back_expansion_node(new_words[index], expansion->type,
									new_list) < 0)
			return (free_no_used_words(new_words, new_words + index), -1);
		if (add_back_expansion_node(NULL, SPACE, new_list) < 0)
			return (free_no_used_words(new_words, new_words + index), -1);
		index++;
	}
	free(new_words);
	return (0);
}

static void	free_no_used_words(char **words, char **not_used_words)
{
	while (*not_used_words != NULL)
	{
		free(*not_used_words);
		not_used_words++;
	}
	free(words);
}
