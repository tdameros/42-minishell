/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:33:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/16 22:33:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

char			*strdup_without_quote(char *command);
static size_t	strlen_without_quote(char *command);

int	remove_quotes(t_list *tokens)
{
	t_token	*token;
	char	*parse_command;

	if (tokens == NULL)
		return (0);
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type != OPERATOR)
		{
			parse_command = strdup_without_quote(token->name);
			free(token->name);
			token->name = parse_command;
		}
		tokens = tokens->next;
	}
	return (0);
}

char	*strdup_without_quote(char *command)
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
