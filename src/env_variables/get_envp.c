/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:19:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 08:00:14 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	add_variables(char **envp, t_list *variables, int *i);

char	**get_envp(t_hashmap env_variables)
{
	char	**envp;
	int		i;
	int		envp_i;

	envp = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1));
	if (envp == NULL)
		return (NULL);
	envp_i = 0;
	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		if (add_variables(envp, env_variables[i], &envp_i))
		{
			ft_free_split(envp);
			return (NULL);
		}
		i++;
	}
	envp[envp_i] = NULL;
	return (envp);
}

static int	add_variables(char **envp, t_list *variables, int *envp_i)
{
	char				*join[3];
	t_hashmap_content	*hashmap_content;

	join[2] = NULL;
	while (variables != NULL)
	{
		hashmap_content = variables->content;
		join[0] = hashmap_content->target;
		join[1] = hashmap_content->content;
		envp[*envp_i] = ft_join_strs(join, "=");
		if (envp[*envp_i] == NULL)
			return (-1);
		(*envp_i)++;
		variables = variables->next;
	}
	return (0);
}