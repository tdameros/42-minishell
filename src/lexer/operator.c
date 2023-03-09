/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 01:50:02 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"

int	get_operator(char *string)
{
	if (ft_strncmp(string, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(string, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(string, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(string, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(string, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(string, ">", 1) == 0)
		return (OUTPUT_REDIRECT);
	else if (ft_strncmp(string, "<", 1) == 0)
		return (INPUT_REDIRECT);
	else if (ft_strncmp(string, "(", 1) == 0)
		return (OPEN_PARENTHESES);
	else if (ft_strncmp(string, ")", 1) == 0)
		return (CLOSE_PARENTHESES);
	return (-1);
}

int	add_operator_token(t_list **tokens, enum e_operators operator)
{
	t_token	*token;
	t_list	*element;

	token = create_token(OPERATOR, operator, NULL);
	if (token == NULL)
		return (-1);
	element = ft_lstnew((void *) token);
	if (element == NULL)
	{
		free(token);
		return (-1);
	}
	ft_lstadd_front(tokens, element);
	return (0);
}

bool	is_file_operator_token(t_token *token)
{
	if (token == NULL || token->type != OPERATOR)
		return (0);
	return (token->operator == INPUT_REDIRECT
		|| token->operator == OUTPUT_REDIRECT
		|| token->operator == HERE_DOC
		|| token->operator == APPEND);
}

bool	is_operator(char *command)
{
	return (get_operator(command) >= 0);
}
