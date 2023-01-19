/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:34:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/16 22:34:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_simple_quote(char *command);
static int	is_valid_double_quote(char *command);

int	is_valid_quote(char *command)
{
	return (is_valid_double_quote(command) && is_valid_simple_quote(command));
}

static int	is_valid_simple_quote(char *command)
{
	int	count;
	int	double_quote;

	count = 0;
	double_quote = 0;
	while (*command)
	{
		if (*command == '\'' && double_quote % 2 == 0)
			count++;
		else if (*command == '"' && count % 2 == 0)
			double_quote++;
		command++;
	}
	return (count % 2 == 0);
}

static int	is_valid_double_quote(char *command)
{
	int	count;
	int	simple_quote;

	count = 0;
	simple_quote = 0;
	while (*command)
	{
		if (*command == '"' && simple_quote % 2 == 0)
			count++;
		else if (*command == '\'' && count % 2 == 0)
			simple_quote++;
		command++;
	}
	return (count % 2 == 0);
}
