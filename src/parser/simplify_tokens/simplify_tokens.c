/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:09 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 18:09:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "exit_code.h"
#include "parser.h"

static int	handle_non_operator_or_file_operator(t_list **tokens,
				t_hashmap env_variables, t_list **simplified_tokens);

int	simplify_tokens(t_list **tokens, t_hashmap env_variables)
{
	int		error;
	t_list	*simplified_tokens;
	t_token	*token;

	simplified_tokens = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPERATOR && is_file_operator_token(token) == 0)
		{
			ft_lst_push(&simplified_tokens, tokens);
			continue ;
		}
		error = handle_non_operator_or_file_operator(tokens, env_variables,
				&simplified_tokens);
		if (error)
		{
			ft_lstclear(&simplified_tokens, &free_token);
			ft_lstclear(tokens, &free_token);
			return (error);
		}
	}
	*tokens = get_subshells(ft_lst_reverse(&simplified_tokens));
	return (0);
}

static int	handle_non_operator_or_file_operator(t_list **tokens,
				t_hashmap env_variables, t_list **simplified_tokens)
{
	int		error;
	t_token	*new_command;
	t_list	*new_node;

	error = get_new_command(tokens, env_variables, &new_command);
	if (error)
	{
		if (error == MALLOC_FAILED)
		{
			print_error(NULL, "handle_non_operator_or_file_operator()",
				get_error());
			return (exit_code(MALLOC_FAILED));
		}
		return (exit_code(FILE_COUNT_IS_BAD));
	}
	new_node = ft_lstnew(new_command);
	if (new_node == NULL)
	{
		free_token(new_command);
		return (MALLOC_FAILED);
	}
	ft_lstadd_front(simplified_tokens, new_node);
	return (0);
}
