/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tildes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:48:08 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 02:05:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expansions.h"

static bool	is_tilde(t_expansion *expansion);
static bool	is_prefix_tilde(char *str);
static int	change_tilde(t_expansion *expansion, t_hashmap env_variables);
static int	change_prefix_tilde(t_expansion *expansion,
				t_hashmap env_variables);

int	replace_tildes(t_list **tokens, t_hashmap env_variables)
{
	t_list		*token;
	t_expansion	*expansion;
	int			quote;

	token = *tokens;
	quote = -1;
	while (token != NULL)
	{
		expansion = token->content;
		if ((int) expansion->type == quote)
			quote = -1;
		else if (quote == -1 && (expansion->type == SIMPLE_QUOTE
				|| expansion->type == DOUBLE_QUOTE))
			quote = expansion->type;
		if (quote == -1 && is_tilde(expansion) && token->next == NULL)
		{
			if (change_tilde(expansion, env_variables) < 0)
				return (-1);
		}
		token = token->next;
	}
	return (0);
}

static bool	is_tilde(t_expansion *expansion)
{
	char	*str;

	if (expansion->type != WORD)
		return (false);
	str = expansion->content;
	if (str[0] == '~' && (str[1] == '/' || str[1] == '\0'))
		return (true);
	return (is_prefix_tilde(str));
}

static bool	is_prefix_tilde(char *str)
{
	if (str[0] == '~' && str[1] == '+' && (str[2] == '/' || str[2] == '\0'))
		return (true);
	if (str[0] == '~' && str[1] == '-' && (str[2] == '/' || str[2] == '\0'))
		return (true);
	return (false);
}

static int	change_tilde(t_expansion *expansion, t_hashmap env_variables)
{
	char	*new_content;
	char	*tilde_path;

	if (is_prefix_tilde(expansion->content))
		return (change_prefix_tilde(expansion, env_variables));
	else
	{
		tilde_path = ft_hm_get_content(env_variables, "HOME");
		if (tilde_path == NULL)
			return (0);
		new_content = ft_strjoin(tilde_path, expansion->content + 1);
		if (new_content == NULL)
			return (-1);
		free(expansion->content);
		expansion->content = new_content;
	}
	return (0);
}

static int	change_prefix_tilde(t_expansion *expansion, t_hashmap env_variables)
{
	char	*new_content;
	char	*tilde_path;

	tilde_path = NULL;
	if (expansion->content[1] == '+')
		tilde_path = ft_hm_get_content(env_variables, "PWD");
	else if (expansion->content[1] == '-')
		tilde_path = ft_hm_get_content(env_variables, "OLDPWD");
	if (tilde_path == NULL)
		return (0);
	new_content = ft_strjoin(tilde_path, expansion->content + 2);
	if (new_content == NULL)
		return (-1);
	free(expansion->content);
	expansion->content = new_content;
	return (0);
}
