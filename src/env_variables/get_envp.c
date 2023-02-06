/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:19:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 15:57:57 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"
#include <stdlib.h>

static int	add_variables_non_empty(char **envp, t_list *variables, int *envp_i,
				char *executable_path);
static int	add_variables_all(char **envp, t_list *variables,
				int *envp_i);

char	**get_non_empty_envp(t_hashmap env_variables, char *executable_path)
{
	char	**envp;
	int		i;
	int		envp_i;

	envp = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1 - 1));
	if (envp == NULL)
		return (NULL);
	envp_i = 0;
	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		if (add_variables_non_empty(envp, env_variables[i], &envp_i,
				executable_path))
		{
			ft_free_split(envp);
			return (NULL);
		}
		i++;
	}
	envp[envp_i] = NULL;
	return (envp);
}

static int	add_variables_non_empty(char **envp, t_list *variables, int *envp_i,
				char *executable_path)
{
	char				*join[3];
	t_hashmap_content	*hashmap_content;

	join[2] = NULL;
	while (variables != NULL)
	{
		hashmap_content = variables->content;
		if (hashmap_content->content != NULL
			&& ft_strcmp(hashmap_content->target, LAST_EXIT_CODE))
		{
			join[0] = hashmap_content->target;
			if (ft_strcmp("_", hashmap_content->target) == 0)
				join[1] = ft_strdup(executable_path);
			else
				join[1] = hashmap_content->content;
			envp[*envp_i] = ft_join_strs(join, "=");
			if (ft_strcmp("_", hashmap_content->target) == 0)
				free(join[1]);
			if (envp[*envp_i] == NULL)
				return (-1);
			(*envp_i)++;
		}
		variables = variables->next;
	}
	return (0);
}

char	**get_all_envp(t_hashmap env_variables)
{
	char	**envp;
	int		i;
	int		envp_i;

	envp = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1 - 1));
	if (envp == NULL)
		return (NULL);
	envp_i = 0;
	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		if (add_variables_all(envp, env_variables[i], &envp_i))
		{
			ft_free_split(envp);
			return (NULL);
		}
		i++;
	}
	envp[envp_i] = NULL;
	return (envp);
}

static int	add_variables_all(char **envp, t_list *variables,
				int *envp_i)
{
	char				*join[3];
	t_hashmap_content	*hashmap_content;

	join[2] = NULL;
	while (variables != NULL)
	{
		hashmap_content = variables->content;
		if (ft_strcmp(hashmap_content->target, LAST_EXIT_CODE))
		{
			if (hashmap_content->content == NULL)
				envp[*envp_i] = ft_strdup(hashmap_content->target);
			else
			{
				join[0] = hashmap_content->target;
				join[1] = hashmap_content->content;
				envp[*envp_i] = ft_join_strs(join, "=");
			}
			if (envp[*envp_i] == NULL)
				return (-1);
			(*envp_i)++;
		}
		variables = variables->next;
	}
	return (0);
}
