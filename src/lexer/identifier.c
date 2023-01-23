/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:57:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/18 16:57:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	get_index_end_token(char *command)
{
	int		index;
	char	quote;
	int		count_quote;

	index = 0;
	count_quote = 0;
	if (*command == '"' || *command == '\'')
	{
		quote = *command;
		while (command[index] != '\0')
		{
			if (command[index] == quote)
				count_quote++;
			if (get_operator(command + index) >= 0 && count_quote % 2 == 0)
				return (index);
			index++;
		}
	}
	else
	{
		while (get_operator(command + index) < 0 && command[index] != ' ' && command[index] != '\0')
			index++;
	}
	return (index);
}

int	get_index_next_token(char *command)
{
	int	index;

	index = 0;
	if (get_operator(command) >= 0)
	{
		if (command[0] != '\0' && command[0] == command[1])
			index += 2;
		else
			index++;
	}
	else
		index += get_index_end_token(command);
	while (command[index] == ' ')
		index++;
	return (index);
}
