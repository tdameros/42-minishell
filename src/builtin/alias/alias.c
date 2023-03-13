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

#include "env_variables.h"
#include "error.h"
#include "exit_code.h"
#include "builtin.h"

static int	print_alias(t_hashmap alias);
static int	print_alias_variables(char **alias);
static int	add_alias_variables(char **args, t_hashmap alias);
static int	print_simple_alias(char *key, t_hashmap alias);

int	alias(char **args, t_hashmap alias)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if (print_alias(alias) < 0)
		{
			print_error("alias", args[index], strerror(errno));
			return (set_exit_code(1));
		}
	}
	else
		return (set_exit_code(add_alias_variables(args + index, alias)));
	return (set_exit_code(0));
}

static int	print_alias(t_hashmap alias)
{
	char	**aliases;

	if (ft_hm_size(alias) == 0)
		return (0);
	aliases = get_all_aliases(alias);
	if (aliases == NULL)
		return (-1);
	if (ft_msort_str(aliases, 0, ft_split_size(aliases) - 1) < 0)
	{
		ft_free_split(aliases);
		return (-1);
	}
	return (print_alias_variables(aliases));
}

static int	print_alias_variables(char **alias)
{
	size_t	index;

	index = 0;
	while (alias[index] != NULL)
	{
		ft_printf("alias %s\n", alias[index]);
		free(alias[index]);
		index++;
	}
	free(alias);
	return (0);
}

static int	add_alias_variables(char **args, t_hashmap alias)
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
			if (print_simple_alias(*args, alias) == 1)
				exit_code = 1;
		}
		else
		{
			*equal = '\0';
			value = ft_strdup(equal + 1);
			if (value == NULL)
				return (-1);
			if (ft_hm_add_elem(alias, *args, value, &free) < 0)
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
		ft_printf("alias %s='%s'\n", key, value);
	return (0);
}
