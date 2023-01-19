/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/20 00:35:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

enum e_type	identify_token(t_token *previous_token, char *command);
int			is_file_operator_token(t_token *token);
int			get_index_end_token(char *command);
int			get_index_next_token(char *command);
int			add_token(t_list **tokens, enum e_type type,
				enum e_operators operator, char *name);
t_token		*create_token(enum e_type type, enum e_operators operator,
				char *name);

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
		while (get_operator(command + index) < 0 && command[index] != ' '
			&& command[index] != '\0')
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

int	add_token(t_list **tokens, enum e_type type, enum e_operators operator,
		char *name)
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
	token->args = NULL;
	token->files = NULL;
	return (token);
}

void	print_tokens(t_list *tokens)
{
	int		i;
	t_list	*cursor;

	while (tokens != NULL)
	{
		ft_printf("Type: %d\n", ((t_token *)tokens->content)->type);
		ft_printf("Operator: %d\n", ((t_token *)tokens->content)->operator);
		ft_printf("Name: %s\n", ((t_token *)tokens->content)->name);
		ft_printf("Args: ");
		i = 0;
		if (((t_token *)tokens->content)->args != NULL)
			while (((t_token *)tokens->content)->args[i] != NULL)
				ft_printf("%s, ", ((t_token *)tokens->content)->args[i++]);
		ft_printf("(null)\n");
		ft_printf("Files: ");
		cursor = ((t_token *)tokens->content)->files;
		while (cursor != NULL)
		{
			ft_printf("Name: %s, Operator: %d -> ",
				((t_token *)cursor->content)->name,
				((t_token *)cursor->content)->operator);
				cursor = cursor->next;
		}
		ft_printf("(null)\n");
		ft_printf("--------------\n");
		tokens = tokens->next;
	}
}

void	free_token(void *token)
{
	ft_free_split(((t_token *)token)->args);
	free(((t_token *)token)->name);
	if (((t_token *)token)->files != NULL)
		ft_lstclear(&((t_token *)token)->files, &free_token);
	free(token);
}
