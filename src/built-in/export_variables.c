/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:10:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/22 22:10:59 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "expansions.h"

static int		add_variable(char *variable, t_hashmap env_variables);
static int		add_value(char *key, char *value, t_hashmap env_variables);
static int		addition_export(char *key, char *value,
					t_hashmap env_variables);
static bool		is_valid_key(char *key);

int	export_variables(char **args, t_hashmap env_variables)
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
	return (add_value(key, value, env_variables));
}

static int	add_value(char *key, char *value, t_hashmap env_variables)
{
	if (key[ft_strlen(key) - 1] == '+')
		return (addition_export(key, value, env_variables));
	else if (ft_hm_add_elem(env_variables, key, value, free) < 0)
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
	if (!ft_isalpha(key[index]) && key[index] != '_')
		return (false);
	while (key[index] != '\0')
	{
		if (key[index] == '+' && key[index + 1] == '\0')
			return (true);
		if (!ft_isalnum(key[index]) && key[index] != '_')
			return (false);
		index++;
	}
	return (true);
}

static int	addition_export(char *key, char *value, t_hashmap env_variables)
{
	char	*previous_value;
	char	*tmp;

	key[ft_strlen(key) - 1] = '\0';
	previous_value = ft_hm_get_content(env_variables, key);
	if (previous_value != NULL)
	{
		tmp = ft_strjoin(previous_value, value);
		free(value);
		value = tmp;
	}
	if (value == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, key, value, free) < 0)
	{
		free(value);
		return (-1);
	}
	return (1);
}
