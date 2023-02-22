/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:56:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/29 15:56:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env_variables.h"
#include "expansions.h"

static size_t	get_len_with_parameters_quote(char *string, t_hashmap env);
static size_t	get_len_with_parameters(char *string, t_hashmap env);

int	insert_parameters_in_args(char **args, t_hashmap env_variables)
{
	char	*arg;

	while (*args != NULL)
	{
		arg = strdup_with_parameters_quote(*args, env_variables);
		if (arg == NULL)
			return (-1);
		free(*args);
		*args = arg;
		args++;
	}
	return (0);
}

char	*strdup_with_parameters_quote(char *string, t_hashmap env_variables)
{
	char	*string_with_env;
	char	*value;
	char	quote;
	size_t	index;
	size_t	size;

	size = get_len_with_parameters_quote(string, env_variables) + 1;
	string_with_env = ft_calloc(size, sizeof(char));
	if (string_with_env == NULL)
		return (NULL);
	quote = 0;
	index = 0;
	while (*string != '\0')
	{
		if (get_current_quote(string, &quote) != '\'' && is_parameter(string, quote))
		{
			value = get_parameter_value(string, env_variables);
			if (value != NULL)
				index = ft_strlcat(string_with_env, value, size);
			string = get_end_parameter(string);
		}
		else
			string_with_env[index++] = *(string++);
	}
	return (string_with_env);
}

static size_t	get_len_with_parameters_quote(char *string, t_hashmap env)
{
	size_t	len;
	char	*value;
	char	quote;

	len = 0;
	quote = 0;
	while (*string != '\0')
	{
		if (get_current_quote(string, &quote) != '\''
			&& is_parameter(string, quote))
		{
			value = get_parameter_value(string, env);
			if (value != NULL)
				len += ft_strlen(value);
			string = get_end_parameter(string);
		}
		else
		{
			len++;
			string++;
		}
	}
	return (len);
}

char	*strdup_with_parameters(char *string, t_hashmap env_variables)
{
	char	*string_with_env;
	char	*value;
	size_t	index;
	size_t	size;

	size = get_len_with_parameters(string, env_variables) + 1;
	string_with_env = ft_calloc(size, sizeof(char));
	if (string_with_env == NULL)
		return (NULL);
	index = 0;
	while (*string != '\0')
	{
		if (is_parameter(string, 1))
		{
			value = get_parameter_value(string, env_variables);
			if (value != NULL)
				index = ft_strlcat(string_with_env, value, size);
			string = get_end_parameter(string);
		}
		else
			string_with_env[index++] = *(string++);
	}
	return (string_with_env);
}

static size_t	get_len_with_parameters(char *string, t_hashmap env)
{
	size_t	len;
	char	*value;

	len = 0;
	while (*string != '\0')
	{
		if (is_parameter(string, 1))
		{
			value = get_parameter_value(string, env);
			if (value != NULL)
				len += ft_strlen(value);
			string = get_end_parameter(string);
		}
		else
		{
			len++;
			string++;
		}
	}
	return (len);
}
