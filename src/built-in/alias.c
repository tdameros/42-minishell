/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdamerose@student.42lyon.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:24:39 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 17:24:40 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "env_variables.h"
#include "error.h"
#include "exit_code.h"

static int	print_alias(t_hashmap alias);
static int	print_alias_variables(char **alias);
static int	add_alias_variables(char **args, t_hashmap alias_variable);
static int	print_simple_alias(char *key, t_hashmap alias);

int	alias(char **args, t_hashmap alias_variables)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if (print_alias(alias_variables) < 0)
		{
			print_error("alias", args[index], strerror(errno));
			return (exit_code(1));
		}
	}
	else
		return (exit_code(add_alias_variables(args + index, alias_variables)));
	return (exit_code(0));
}

static int	print_alias(t_hashmap alias)
{
	char	**envp;

	if (ft_hm_size(alias) == 0)
		return (0);
	envp = get_all_envp(alias);
	if (envp == NULL)
		return (-1);
	if (ft_msort_str(envp, 0, ft_split_size(envp) - 1) < 0)
	{
		ft_free_split(envp);
		return (-1);
	}
	return (print_alias_variables(envp));
}

static int	print_alias_variables(char **alias)
{
	char	*equal;
	size_t	index;

	index = 0;
	while (alias[index] != NULL)
	{
		equal = ft_strchr(alias[index], '=');
		if (equal == NULL)
			ft_printf("alias %s\n", alias[index]);
		else
		{
			*equal = '\0';
			ft_printf("alias %s='%s'\n", alias[index], equal + 1);
		}
		free(alias[index]);
		index++;
	}
	free(alias);
	return (0);
}

static int	add_alias_variables(char **args, t_hashmap alias_variable)
{
	char	*value;
	char	*equal;
	int		exit_code;

	exit_code = 0;
	while (*args != NULL)
	{
		equal = ft_strchr(*args, '=');
		if (equal == NULL)
		{
			if (print_simple_alias(*args, alias_variable) == 1)
				exit_code = 1;
		}
		else
		{
			*equal = '\0';
			value = ft_strdup(equal + 1);
			if (value == NULL)
				return (-1);
			if (ft_hm_add_elem(alias_variable, *args, value, &free) < 0)
				return (free(value), -1);
		}
		args++;
	}
	return (exit_code);
}

static int	print_simple_alias(char *key, t_hashmap alias)
{
	char	*value;

	value = ft_hm_get_content(alias, key);
	if (value == NULL)
	{
		print_error("alias", key, "not found");
		return (1);
	}
	else
		ft_printf("alias %s='%s'", key, value);
	return (0);
}
