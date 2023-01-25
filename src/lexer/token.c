/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/23 18:30:51 by vfries           ###   ########lyon.fr   */
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
		{
			ft_printf("{ ");
			while (((t_token *)tokens->content)->args[i] != NULL)
				ft_printf("%s, ", ((t_token *)tokens->content)->args[i++]);
		}
		ft_printf("(null)");
		if (((t_token *)tokens->content)->args != NULL)
			ft_printf(" }\n");
		else
			ft_printf("\n");
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
	if (token == NULL)
		return ;
	ft_free_split(((t_token *)token)->args);
	free(((t_token *)token)->name);
	if (((t_token *)token)->files != NULL)
		ft_lstclear(&((t_token *)token)->files, &free_token);
	free(token);
}
