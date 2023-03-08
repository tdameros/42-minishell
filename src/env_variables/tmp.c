/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 00:44:07 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 16:11:51 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>

static bool	fill_env_variables(t_hashmap env_variables, char **envp);
static char	*get_var_name(char *envp_var);
static char	*get_var_content(char *envp_var, char *var_name);
static void	fix_env_variables(t_hashmap env_variables);

t_hashmap	get_env_variables(char **envp, char *minishell_path)
{
	t_hashmap	env_variables;

	if (envp == NULL)
	{
		ft_printf("ERROR: %s(): envp is NULL\n", __FUNCTION__);
		return (NULL);
	}
	env_variables = ft_hm_init();
	if (env_variables == NULL)
		return (NULL);
	if (fill_env_variables(env_variables, envp))
		ft_hm_clear(&env_variables, &free);
	fix_env_variables(env_variables);
	if (ft_hm_add_elem(env_variables, "SHELL", minishell_path, &free) < 0)
	{
		free(minishell_path);
		ft_hm_clear(&env_variables, &free);
		return (NULL);
	}
	return (env_variables);
}

static bool	fill_env_variables(t_hashmap env_variables, char **envp)
{
	size_t	i;
	char	*var_name;
	char	*var_content;

	i = 0;
	while (envp[i] != NULL)
	{
		var_name = get_var_name(envp[i]);
		var_content = get_var_content(envp[i], var_name);
		if (var_name == NULL || var_content == NULL)
		{
			free(var_name);
			free(var_content);
			return (true);
		}
		ft_hm_add_elem(env_variables, var_name, var_content, &free);
		free(var_name);
		i++;
	}
	return (false);
}

static char	*get_var_name(char *envp_var)
{
	size_t	size;
	char	*var_name;

	size = 0;
	while (envp_var[size] != '\0' && envp_var[size] != '=')
		size++;
	var_name = malloc(sizeof(char) * (size + 1));
	if (var_name == NULL)
		return (NULL);
	var_name[size] = '\0';
	while (size-- > 0)
		var_name[size] = envp_var[size];
	return (var_name);
}

static char	*get_var_content(char *envp_var, char *var_name)
{
	if (var_name == NULL)
		return (NULL);
	while (*envp_var != '\0' && *envp_var != '=')
		envp_var++;
	if (*envp_var == '=')
		envp_var++;
	return (ft_strdup(envp_var));
}

static void	fix_env_variables(t_hashmap env_variables)
{
	t_hashmap_content	*tmp;
	char				*tmp_str;
	struct stat			stat_ptr;

	tmp = ft_hm_get_elem(env_variables, "SHLVL");
	if (tmp == NULL)
		ft_hm_add_elem(env_variables, "SHLVL", ft_strdup("1"), &free);
	else
	{
		tmp_str = ft_itoa(ft_atoi(tmp->content) + 1);
		if (tmp_str != NULL)
		{
			free(tmp->content);
			tmp->content = tmp_str;
		}
	}
	tmp_str = getcwd(NULL, 0);
	if (ft_hm_add_elem(env_variables, "PWD", tmp_str, &free))
		free(tmp_str);
	tmp = ft_hm_get_elem(env_variables, "OLDPWD");
	if (tmp == NULL
		|| (stat(tmp->content, &stat_ptr) != 0
			&& (stat_ptr.st_mode & S_IFDIR) == 0))
		ft_hm_add_elem(env_variables, "OLDPWD", NULL, &free);
}
