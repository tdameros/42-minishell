/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expressions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:26:54 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 18:26:55 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

ssize_t	add_simple_quotes_expression(char *arg, t_list **expansions)
{
	char	*word;
	char	*next_quote;

	if (*arg != '\'')
		return (-1);
	arg++;
	next_quote = ft_strchr(arg, '\'');
	if (next_quote == NULL)
		return (-1);
	if (add_back_expansion_node(NULL, SIMPLE_QUOTE, expansions) < 0)
		return (-1);
	word = ft_substr(arg, 0, next_quote - arg);
	if (word == NULL)
		return (-1);
	if (add_back_expansion_node(word, WORD, expansions) < 0)
		return (free(word), -1);
	if (add_back_expansion_node(NULL, SIMPLE_QUOTE, expansions) < 0)
		return (-1);
	return (next_quote - arg + 2);
}

ssize_t	add_dollar_expression(char *arg, t_list **expansions)
{
	char	*end_parameter;
	char	*word;

	if (*arg != '$')
		return (-1);
	arg++;
	end_parameter = get_end_dollar_parameter(arg) + 1;
	if (add_back_expansion_node(NULL, DOLLAR, expansions) < 0)
		return (-1);
	word = ft_substr(arg, 0, end_parameter - arg);
	if (word == NULL)
		return (-1);
	if (add_back_expansion_node(word, WORD, expansions) < 0)
		return (free(word), -1);
	return (end_parameter - arg + 1);
}

ssize_t	add_double_quotes_expression(char *arg, t_list **expansions)
{
	ssize_t	return_len;
	ssize_t	len;

	len = 0;
	if (add_back_expansion_node(NULL, DOUBLE_QUOTE, expansions) < 0)
		return (-1);
	arg++;
	while (*arg != '"')
	{
		if (*arg == '$')
			return_len = add_dollar_expression(arg, expansions);
		else
			return_len = add_expression(arg, "\"$", expansions);
		if (return_len < 0)
			return (-1);
		arg += return_len;
		len += return_len;
	}
	if (add_back_expansion_node(NULL, DOUBLE_QUOTE, expansions) < 0)
		return (-1);
	return (len + 2);
}

ssize_t	add_expression(char *arg, char *delimiters, t_list **expansions)
{
	char	*word;
	char	*end_expression;

	end_expression = get_end_expression(arg, delimiters);
	word = ft_substr(arg, 0, end_expression - arg);
	if (word == NULL)
		return (-1);
	if (add_back_expansion_node(word, WORD, expansions) < 0)
		return (free(word), -1);
	return (end_expression - arg);
}
