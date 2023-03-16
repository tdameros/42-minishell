/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 01:50:12 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"

static int	add_token(t_list **tokens, enum e_type type,
				enum e_operators operator, char *name);

t_list	*get_tokens(char *command)
{
	t_list		*tokens;
	enum e_type	type;
	int			return_code;

	tokens = NULL;
	command = ft_skip_set(command, IFS);
	while (*command != '\0')
	{
		type = identify_token(tokens, command);
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

void	free_token(void *token_void)
{
	t_token	*token;

	if (token_void == NULL)
		return ;
	token = token_void;
	free(token->name);
	ft_free_split(token->args);
	ft_lstclear(&token->files, &free_token);
	ft_lstclear(&token->subshell, &free_token);
	free(token);
}
