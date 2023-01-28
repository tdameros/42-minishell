/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:41:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 17:26:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env_variables.h"
#include "error.h"
#include "built_in.h"

static int		print_sorted_env_variables(t_hashmap env_variables);
static int		add_variable(char *variable, t_hashmap env_variables);
static bool		is_valid_key(char *key);

void	export(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
		return (update_last_exit_code(env_variables,
				print_sorted_env_variables(env_variables)));
	while (args[index] != NULL)
	{
		if (add_variable(args[index], env_variables) < 0)
			print_error("export", args[index], "not a valid identifier");
		index++;
	}
	return (update_last_exit_code(env_variables, 0));
}

static	int	print_sorted_env_variables(t_hashmap env_variables)
{
	char	**envp;
	char	*equal;
	size_t	index;

	envp = get_envp(env_variables);
	if (ft_msort_str(envp, 0, ft_hm_size(env_variables) - 1) < 0)
	{
		ft_free_split(envp);
		return (1);
	}
	index = 0;
	while (envp[index] != NULL)
	{
		equal = ft_strchr(envp[index], '=');
		*equal = '\0';
		ft_printf("declare -x %s", envp[index]);
		ft_printf("=\"%s\"\n", equal + 1);
		free(envp[index]);
		index++;
	}
	free(envp);
	return (0);
}

static int	add_variable(char *variable, t_hashmap env_variables)
{
	char	*key;
	char	*value;
	char	*equal;

	equal = ft_strchr(variable, '=');
	if (equal == variable)
		return (-1);
	key = ft_substr(variable, 0, equal - variable);
	if (!is_valid_key(key))
	{
		free(key);
		return (-1);
	}
	value = ft_strdup(equal + 1);
	ft_hm_add_elem(env_variables, key, value, free);
	free(key);
	return (0);
}

static	bool	is_valid_key(char *key)
{
	size_t	index;

	index = 0;
	if (!ft_isalpha(key[index]))
		return (false);
	while (key[index] != '\0')
	{
		if (!ft_isalnum(key[index]) && key[index] != '_')
			return (false);
		index++;
	}
	return (true);
}
