/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/15 15:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

int	get_index_end_token(char *string)
{
	int	index;

	index = 0;
	while (get_operator(string + index) < 0 && string[index] != ' ' && string[index] != '\0')
		index++;
	return (index);
}

t_list	*get_tokens(char *command)
{
	t_list	*tokens;
	t_token *previous_token;
	char	*name;

	(void) command;
	tokens = NULL;
	previous_token = NULL;
	while (*command != '\0')
	{
		if (get_operator(command) < 0)
		{
			name = ft_substr(command, 0, get_index_end_token(command));
			if (tokens != NULL)
				previous_token = tokens->content;
			if (previous_token == NULL)
				add_operator_token(&tokens, 0, COMMAND, name);
			else if (previous_token->type == OPERATOR && (previous_token->operator >= 5 && previous_token->operator <= 8))
				add_operator_token(&tokens, 0, PATH_FILE, name);
			else if (previous_token->type == OPERATOR)
				add_operator_token(&tokens, 0, COMMAND, name);
			else
				add_operator_token(&tokens, 0, ARGUMENT, name);
		}
		else
		{
			add_operator_token(&tokens, get_operator(command), OPERATOR, NULL);
		}
		if (get_index_end_token(command) == 0)
		{
			if (command[0] != '\0' && command[0] == command[1])
				command += 2;
			else
				command++;
		}
		else
			command += get_index_end_token(command);
		while (*command == ' ')
			command++;
	}
	ft_lst_reverse(&tokens);
	return (tokens);
}

t_token	*create_token(enum e_type type, enum e_operators operator, char *name)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->operator = operator;
	token->name = name;
	return (token);
}

void	print_tokens(t_list *tokens)
{
	while (tokens != NULL)
	{
		ft_printf("Type: %d\n", ((t_token *) tokens->content)->type);
		ft_printf("Operator: %d\n", ((t_token *) tokens->content)->operator);
		ft_printf("Name: %s\n", ((t_token *) tokens->content)->name);
		ft_printf("--------------\n");
		tokens = tokens->next;
	}
}