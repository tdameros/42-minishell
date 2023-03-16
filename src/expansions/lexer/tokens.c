/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:27:23 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 02:00:08 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

t_list	*get_expansion_tokens(char *arg)
{
	t_list	*tokens;
	ssize_t	return_len;

	tokens = NULL;
	while (*arg != '\0')
	{
		if (*arg == '\'')
			return_len = add_simple_quotes_expression(arg, &tokens);
		else if (*arg == '$')
			return_len = add_dollar_expression(arg, &tokens);
		else if (*arg == '\"')
			return_len = add_double_quotes_expression(arg, &tokens);
		else
			return_len = add_expression(arg, "\"$'", &tokens);
		if (return_len < 0)
		{
			ft_lstclear(&tokens, free_expansion);
			return (NULL);
		}
		arg += return_len;
	}
	return (tokens);
}
