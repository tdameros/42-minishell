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

enum e_type	identify_token(t_token *previous_token, char *command);
int	is_file_operator_token(t_token *token);
int	get_index_end_token(char *command);
int	get_index_next_token(char *command);
int	add_token(t_list **tokens, enum e_type type, enum e_operators operator, char *name);
t_token	*create_token(enum e_type type, enum e_operators operator, char *name);

t_list	*get_tokens(char *command)
{
	t_list		*tokens;
	enum e_type	type;
	int			return_code;

	tokens = NULL;
	while (*command != '\0')
	{
		if (tokens == NULL)
			type = identify_token(NULL, command);
		else
			type = identify_token(tokens->content, command);
		if (type == OPERATOR)
			return_code = add_operator_token(&tokens, get_operator(command));
		else
			return_code = add_token(&tokens, type, 0,
					ft_substr(command, 0, get_index_end_token(command)));
		command += get_index_next_token(command);
		if (return_code < 0)
			exit(1);
	}
	ft_lst_reverse(&tokens);
	return (tokens);
}

enum e_type	identify_token(t_token *previous_token, char *command)
{
	if (get_operator(command) >= 0)
		return (OPERATOR);
	else if (is_file_operator_token(previous_token))
		return (PATH_FILE);
	else if (previous_token == NULL || previous_token->type == OPERATOR)
		return (COMMAND);
	else
		return (ARGUMENT);
}

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

int	add_token(t_list **tokens, enum e_type type, enum e_operators operator, char *name)
{
	t_token	*token;
	t_list	*element;

	if (tokens == NULL || name == NULL)
		return (-1);
	token = create_token(type, operator, name);
	if (token == NULL)
		return (-1);
	element = ft_lstnew((void *) token);
	if (element == NULL)
	{
		free(token);
		free(name);
		return (-1);
	}
	ft_lstadd_front(tokens, element);
	return (0);
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