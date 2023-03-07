/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:39:41 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 19:39:42 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len_with_parameters(char *string, t_hashmap env);
char			*get_parameter_value(char *parameter, t_hashmap env_variables);
char			*get_end_parameter(char *string);
bool			is_parameter(char *string, char quote);

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

char	*get_parameter_value(char *parameter, t_hashmap env_variables)
{
	char	*end_parameter;
	char	tmp;
	char	*value;

	end_parameter = get_end_parameter(parameter);
	tmp = *end_parameter;
	*end_parameter = '\0';
	value = ft_hm_get_content(env_variables, parameter + 1);
	*end_parameter = tmp;
	return (value);
}

char	*get_end_parameter(char *string)
{
	size_t	index;

	index = 1;
	if (string[0] != '$')
		return (string);
	if (!ft_isalnum(string[index])
		&& string[index] != '?' && string[index] != '_')
		return (string + 1);
	if (ft_isdigit(string[index]) || string[index] == '?')
		return (string + index + 1);
	while (ft_isalnum(string[index]) || string[index] == '_')
		index++;
	return (string + index);
}

bool	is_parameter(char *string, char quote)
{
	if (quote == 0)
		return (string[0] == '$' && (ft_isalnum(string[1])
				|| string[1] == '_' || string[1] == '?'
				|| string[1] == '\'' || string[1] == '"'));
	return (string[0] == '$' && (ft_isalnum(string[1])
			|| string[1] == '_' || string[1] == '?'));
}
