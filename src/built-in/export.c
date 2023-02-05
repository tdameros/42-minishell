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
#include "expansions.h"

static int		print_sorted_env_variables(t_hashmap env_variables);
static	int		export_variables(char **args, t_hashmap env_variables);
static int		add_variable(char *variable, t_hashmap env_variables);
static bool		is_valid_key(char *key);

void	export(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if (print_sorted_env_variables(env_variables) < 0)
		{
			print_error("export", args[index], strerror(errno));
			return (update_last_exit_code(env_variables, 1));
		}
	}
	else
		return (update_last_exit_code(env_variables, export_variables(args + index, env_variables)));
	return (update_last_exit_code(env_variables, 0));
}

static	int	print_sorted_env_variables(t_hashmap env_variables)
{
	char	**envp;
	char	*equal;
	size_t	index;

	if (ft_hm_size(env_variables) == 1)
		return (0);
	envp = get_envp(env_variables);
	if (envp == NULL)
		return (-1);
	if (ft_msort_str(envp, 0, ft_split_size(envp) - 1) < 0)
	{
		ft_free_split(envp);
		return (-1);
	}
	index = 0;
	while (envp[index] != NULL)
	{
		equal = ft_strchr(envp[index], '=');
		*equal = '\0';
		ft_printf("declare -x %s=\"%s\"\n", envp[index], equal + 1);
		free(envp[index]);
		index++;
	}
	free(envp);
	return (0);
}

static	int	export_variables(char **args, t_hashmap env_variables)
{
	size_t	index;
	int		return_code;
	int		result;

	index = 0;
	return_code = 0;
	while (args[index] != NULL)
	{
		result = add_variable(args[index], env_variables);
		if (result == 0)
		{
			print_error("export", args[index], "not a valid identifier");
			return_code = 1;
		}
		else if (result < 0)
		{
			print_error("export", args[index], strerror(errno));
			return (1);
		}
		index++;
	}
	return (return_code);
}

static int	add_variable(char *variable, t_hashmap env_variables)
{
	char	*key;
	char	*value;
	char	*equal;
	char	tmp;

	equal = ft_strchr(variable, '=');
	if (equal == variable || equal == NULL)
		return (is_valid_key(variable));
	tmp = *equal;
	*equal = '\0';
	key = variable;
	if (!is_valid_key(key))
	{
		*equal = tmp;
		return (0);
	}
	value = strdup_without_quote(equal + 1);
	if (value == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, key, value, free) < 0)
	{
		free(value);
		return (-1);
	}
	return (1);
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
