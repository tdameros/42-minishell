/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:19:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:27:08 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "env_variables.h"

static int	add_variables_non_empty(char **envp, t_list *variables, int *envp_i,
				char *executable_path);
static char	**get_fixed_non_empty_envp(char **envp, int i,
				char *executable_path);
static int	add_variables_all(char **envp, t_list *variables,
				int *envp_i);

char	**get_non_empty_envp(t_hashmap env_variables, char *executable_path)
{
	char	**envp;
	int		i;
	int		envp_i;

	if (ft_hm_get_content(env_variables, "_") == NULL)
		envp = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1 - 1 + 1));
	else
		envp = malloc(sizeof(char *) * (ft_hm_size(env_variables) + 1 - 1));
	if (envp == NULL)
		return (NULL);
	envp_i = 0;
	i = -1;
	while (++i < HASHMAP_ARR_SIZE)
	{
		if (add_variables_non_empty(envp, env_variables[i], &envp_i,
				executable_path))
		{
			ft_free_split(envp);
			return (NULL);
		}
	}
	if (ft_hm_get_content(env_variables, "_") == NULL)
		return (get_fixed_non_empty_envp(envp, envp_i, executable_path));
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

static char	**get_fixed_non_empty_envp(char **envp, int i,
				char *executable_path)
{
	if (executable_path == NULL)
		envp[i] = NULL;
	else
		envp[i] = ft_strjoin("_=", executable_path);
	envp[i + 1] = NULL;
	return (envp);
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
