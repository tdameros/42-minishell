/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:24:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/31 18:24:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expansions.h"

static size_t	strlen_without_quote(char *command);

int	remove_quotes_in_args(char **args)
{
	char	*new_arg;
	size_t	index;

	index = 0;
	while (args[index] != NULL)
	{
		new_arg = strdup_without_quote(args[index]);
		if (new_arg == NULL)
			return (-1);
		free(args[index]);
		args[index] = new_arg;
		index++;
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
