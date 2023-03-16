/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:26:20 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 02:05:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expansions.h"

static bool		is_quote(t_list *token);
static size_t	strlen_without_quote(char *command);

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

char	*strdup_without_quotes(char *command)
{
	int		simple_quote;
	int		double_quote;
	int		index;
	char	*str;

	simple_quote = 0;
	double_quote = 0;
	index = 0;
	str = malloc(sizeof(*str) * (strlen_without_quote(command) + 1));
	if (str == NULL)
		return (NULL);
	while (*command != '\0')
	{
		if (*command != '"' && *command != '\'')
			str[index++] = *command;
		else if (*command == '"' && simple_quote % 2 == 0)
			double_quote++;
		else if (*command == '\'' && double_quote % 2 == 0)
			simple_quote++;
		else
			str[index++] = *command;
		command++;
	}
	str[index] = '\0';
	return (str);
}

static size_t	strlen_without_quote(char *command)
{
	int		simple_quote;
	int		double_quote;
	size_t	len;

	simple_quote = 0;
	double_quote = 0;
	len = 0;
	while (*command != '\0')
	{
		if (*command != '"' && *command != '\'')
			len++;
		else if (*command == '"' && simple_quote % 2 == 0)
			double_quote++;
		else if (*command == '\'' && double_quote % 2 == 0)
			simple_quote++;
		else
			len++;
		command++;
	}
	return (len);
}
