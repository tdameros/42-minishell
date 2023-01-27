/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 19:14:13 by vfries           ###   ########lyon.fr   */
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

void	print_tabs(int tabs)
{
	while (tabs-- > 0)
		ft_printf("\t");
}

int	__print_tokens__(t_list *tokens, int tabs)
{
	int		i;
	t_list	*cursor;

	if (tokens == NULL)
		return (-1);
	while (tokens != NULL)
	{
		print_tabs(tabs);
		ft_printf("Type: %d\n", ((t_token *)tokens->content)->type);

		print_tabs(tabs);
		ft_printf("Operator: %d\n", ((t_token *)tokens->content)->operator);

		print_tabs(tabs);
		ft_printf("Name: %s\n", ((t_token *)tokens->content)->name);

		print_tabs(tabs);
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

		print_tabs(tabs);
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

		print_tabs(tabs);
		ft_printf("Subshell:\n");
		if (__print_tokens__(((t_token *)tokens->content)->subshell, tabs + 1)
			== -1)
		{
			print_tabs(tabs);
			ft_printf("(null)\n");
		}

		print_tabs(tabs);
		ft_printf("--------------\n");
		tokens = tokens->next;
	}
	return (0);
}

void	print_tokens(t_list *tokens)
{
	__print_tokens__(tokens, 0);
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
