/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_aliases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:05:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 17:05:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	add_all_aliases_from_node(char **aliases, t_list *variables,
				size_t *aliases_i);

char	**get_all_aliases(t_hashmap env_variables)
{
	char	**aliases;
	size_t	i;
	size_t	aliases_i;

	aliases = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1));
	if (aliases == NULL)
		return (NULL);
	aliases_i = 0;
	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		if (add_all_aliases_from_node(aliases, env_variables[i], &aliases_i))
		{
			ft_free_split(aliases);
			return (NULL);
		}
		i++;
	}
	aliases[aliases_i] = NULL;
	return (aliases);
}

static int	add_all_aliases_from_node(char **aliases, t_list *variables,
				size_t *aliases_i)
{
	t_hashmap_content	*hashmap_content;
	char				*join[5];

	join[1] = "='";
	join[3] = "'";
	join[4] = NULL;
	while (variables != NULL)
	{
		hashmap_content = variables->content;
		if (hashmap_content->content != NULL)
		{
			join[0] = hashmap_content->target;
			join[2] = hashmap_content->content;
			aliases[*aliases_i] = ft_join_strs(join, "");
			if (aliases[*aliases_i] == NULL)
				return (-1);
			(*aliases_i)++;
		}
		variables = variables->next;
	}
	return (0);
}
