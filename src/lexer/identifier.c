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

#include "lexer.h"

static int	skip_quote_in_token(char *command);

enum e_type	identify_token(t_list *previous_tokens, char *command)
{
	t_token	*previous_token;

	if (is_operator(command))
		return (OPERATOR);
	else if (previous_tokens == NULL)
		return (COMMAND);
	previous_token = previous_tokens->content;
	if (is_file_operator_token(previous_token))
		return (PATH_FILE);
	else if (previous_token == NULL || previous_token->type == OPERATOR)
		return (COMMAND);
	while (previous_tokens != NULL)
	{
		previous_token = previous_tokens->content;
		if (!is_file_operator_token(previous_token)
			&& previous_token->type == OPERATOR)
			return (COMMAND);
		if (previous_token->type == COMMAND)
			return (ARGUMENT);
		previous_tokens = previous_tokens->next;
	}
	return (COMMAND);
}

int	get_index_end_token(char *command)
{
	int		index;

	index = 0;
	if (command[index] == '"' || command[index] == '\'')
		index += skip_quote_in_token(command);
	else
	{
		while (!is_operator(command + index)
			&& command[index] != ' ' && command[index] != '\0')
		{
			if (command[index] == '"' || command[index] == '\'')
				index += skip_quote_in_token(command + index);
			else
				index++;
		}
	}
	return (index);
}

static int	skip_quote_in_token(char *command)
{
	int		count_quote;
	int		index;
	char	quote;

	count_quote = 0;
	index = 0;
	if (command[index] != '"' && command[index] != '\'')
		return (index);
	quote = command[index];
	while (command[index] != '\0')
	{
		if (command[index] == quote)
			count_quote++;
		if ((is_operator(command) || command[index] == ' ')
			&& count_quote % 2 == 0)
			return (index);
		index++;
	}
	return (index);
}

int	get_index_next_token(char *command)
{
	int	index;
	int	operator;

	index = 0;
	operator = get_operator(command);
	if (operator >= 0)
	{
		if (command[0] != '\0' && command[0] == command[1]
			&& (command[0] != ')' && command[0] != '('))
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
