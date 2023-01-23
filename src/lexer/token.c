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

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

static int	add_token(t_list **tokens, enum e_type type,
				enum e_operators operator, char *name);

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
			return_code = add_token(&tokens, type, -1,
					ft_substr(command, 0, get_index_end_token(command)));
		command += get_index_next_token(command);
		if (return_code < 0)
		{
			ft_lstclear(&tokens, free_token);
			return (NULL);
		}
	}
	ft_lst_reverse(&tokens);
	return (tokens);
}

static int	add_token(t_list **tokens,
						enum e_type type, enum e_operators operator, char *name)
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

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->operator = operator;
	token->name = name;
	return (token);
}

void	free_token(void *token)
{
	t_token	*cast_token;

	cast_token = token;
	free(cast_token->name);
	free(cast_token);
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
