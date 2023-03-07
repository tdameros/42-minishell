/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replacing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/31 19:16:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static int	replace_alias_in_command(t_token *token, t_hashmap alias);

int	replace_alias(t_list *tokens, t_hashmap alias)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == COMMAND
			&& replace_alias_in_command(token, alias) < 0)
			return (-1);
		else if (token->type == SUBSHELL
			&& replace_alias(token->subshell, alias) < 0)
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}

static int	replace_alias_in_command(t_token *token, t_hashmap alias)
{
	char	*alias_content;

	alias_content = ft_hm_get_content(alias, token->args[0]);
	if (alias_content == NULL)
		return (0);
	alias_content = ft_strdup(alias_content);
	if (alias_content == NULL)
		return (-1);
	free(token->args[0]);
	token->args[0] = alias_content;
	return (0);
}
