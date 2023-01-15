/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:53:41 by vfries            #+#    #+#             */
/*   Updated: 2023/01/15 20:39:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "ft_linked_list.h"
#include "ft_io.h"

static int	handle_operator(t_list **operators, t_list **parsed_tokens,
				t_list **tokens);
static int	handle_close_parentheses(t_list **operators,
				t_list **parsed_tokens);
static void	handle_error(t_list **operators, t_list **parsed_tokens,
				t_list **tokens);
static void	push_all_operators_in_parsed_tokens(t_list **parsed_tokens,
				t_list **operators);

void	parse_tokens(t_list **tokens)
{
	t_list	*parsed_tokens;
	t_list	*operators;

	parsed_tokens = NULL;
	operators = NULL;
	while (*tokens != NULL)
	{
		if (((t_token *)(*tokens)->content)->type == OPERATOR)
		{
			if (handle_operator(&operators, &parsed_tokens, tokens))
				return (handle_error(&operators, &parsed_tokens, tokens));
		}
		else if (((t_token *)(*tokens)->content)->type == COMMAND
			|| ((t_token *)(*tokens)->content)->type == ARGUMENT
			|| ((t_token *)(*tokens)->content)->type == PATH_FILE)
			ft_lst_push(&parsed_tokens, tokens);
		else
		{
			ft_putstr_fd("ERROR: parse_tokens(): Unknown type\n",
				STDOUT_FILENO);
			return (handle_error(&operators, &parsed_tokens, tokens));
		}
	}
	push_all_operators_in_parsed_tokens(&parsed_tokens, &operators);
	*tokens = ft_lst_reverse(parsed_tokens);
}

static int	handle_operator(t_list **operators, t_list **parsed_tokens,
				t_list **tokens)
{
	if (((t_token *)(*tokens)->content)->operator == CLOSE_PARENTHESES)
	{
		*tokens = ft_lst_get_next_free_current(*tokens, &free_token);
		if (handle_close_parentheses(operators, parsed_tokens))
			return (-1);
	}
	else if (((t_token *)(*tokens)->content)->operator == OPEN_PARENTHESES
		|| ((t_token *)(*tokens)->content)->operator == OR
		|| ((t_token *)(*tokens)->content)->operator == AND
		|| ((t_token *)(*tokens)->content)->operator == PIPE
		|| ((t_token *)(*tokens)->content)->operator == INPUT_REDIRECT
		|| ((t_token *)(*tokens)->content)->operator == OUTPUT_REDIRECT
		|| ((t_token *)(*tokens)->content)->operator == HERE_DOC
		|| ((t_token *)(*tokens)->content)->operator == APPEND)
		ft_lst_push(operators, tokens); // TODO This is wrong, need to push previous operators to parsed_tokens till NULL or parentheses
	else
	{
		ft_putstr_fd("ERROR: handle_operator(): Unknown operator\n",
			STDOUT_FILENO);
		return (-1);
	}
	return (0);
}

static int	handle_close_parentheses(t_list **operators, t_list **parsed_tokens)
{
	while (*operators != NULL
		&& ((t_token *)((*operators)->content))->operator != OPEN_PARENTHESES)
		ft_lst_push(parsed_tokens, operators);
	if (*operators == NULL)
	{
		ft_putstr_fd("ERROR: parse_tokens(): Wrong number of parentheses\n",
			STDOUT_FILENO);
		return (-1);
	}
	*operators = ft_lst_get_next_free_current(*operators, &free_token);
	return (0);
}

static void	handle_error(t_list **operators, t_list **parsed_tokens,
				t_list **tokens)
{
	ft_lstclear(tokens, &free_token);
	ft_lstclear(parsed_tokens, &free_token);
	ft_lstclear(operators, &free_token);
}

static void	push_all_operators_in_parsed_tokens(t_list **parsed_tokens,
				t_list **operators)
{
	while (*operators != NULL)
		ft_lst_push(parsed_tokens, operators);
}
