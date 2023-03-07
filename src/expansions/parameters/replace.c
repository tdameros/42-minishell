/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:47:49 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 23:47:50 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static int	apply_parameter_expansion(t_list *expansions, bool between_quotes,
				t_hashmap env_variables);
static int	is_dollar_or_empty_expansion(void *expansion_node);
static int	empty_dollar_parameter(t_list *expansions, bool between_quotes);

int	replace_parameters(t_list **expansions, t_hashmap env_variables)
{
	t_list		*token;
	t_list		**begin;
	int			quote;

	token = *expansions;
	begin = expansions;
	quote = 0;
	while (token != NULL)
	{
		if (((t_expansion *)(token->content))->type == DOUBLE_QUOTE)
			quote = (quote + 1) % 2;
		if (apply_parameter_expansion(token, quote == 1, env_variables) < 0)
			return (-1);
		token = token->next;
	}
	ft_list_remove_if(begin, is_dollar_or_empty_expansion, free_expansion);
	return (0);
}

static int	apply_parameter_expansion(t_list *expansions, bool between_quotes,
										t_hashmap env_variables)
{
	t_expansion	*expansion;
	char		*parameter;

	expansion = expansions->content;
	if (expansion->type != DOLLAR)
		return (0);
	expansion = expansions->next->content;
	if (expansion->content == NULL || ft_strlen(expansion->content) == 0)
		return (empty_dollar_parameter(expansions, between_quotes));
	parameter = ft_hm_get_content(env_variables, expansion->content);
	if (parameter != NULL)
		parameter = ft_strdup(parameter);
	else
		parameter = ft_strdup("");
	if (parameter == NULL)
		return (-1);
	free(expansion->content);
	expansion->content = parameter;
	return (0);
}

static int	is_dollar_or_empty_expansion(void *expansion_node)
{
	t_expansion	*expansion;

	expansion = expansion_node;
	if (expansion->type == DOLLAR)
		return (0);
	if (expansion->type == WORD && expansion->content == NULL)
		return (0);
	if (expansion->type == WORD && ft_strlen(expansion->content) == 0)
		return (0);
	return (-1);
}

static int	empty_dollar_parameter(t_list *expansions, bool between_quotes)
{
	t_expansion	*expansion;
	t_expansion	*next_expansion;
	char		*temp;

	if (expansions->next->next != NULL)
		next_expansion = expansions->next->next->content;
	else
		next_expansion = NULL;
	if (between_quotes
		|| (next_expansion == NULL || next_expansion->type == WORD))
	{
		expansion = expansions->next->content;
		temp = ft_strdup("$");
		if (temp == NULL)
			return (-1);
		free(expansion->content);
		expansion->content = temp;
	}
	return (0);
}
