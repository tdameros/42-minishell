/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:42:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/30 23:42:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "expansions.h"

char	*get_parameter_value(char *parameter, t_hashmap env_variables)
{
	char	*end_parameter;
	char	tmp;
	char	*value;

//	if (!is_parameter(parameter))
//		return (NULL);
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
	if (!ft_isalnum(string[index]) && string[index] != '?' && string[index] != '_')
		return (string + 1);
	if (ft_isdigit(string[index]) || string[index] == '?')
		return (string + index + 1);
	while (ft_isalnum(string[index]) || string[index] == '_')
		index++;
	return (string + index);
}

bool	is_parameter(char *string, char quote)
{
//	ft_printf("%s\n", string);
	if (quote == 0)
		return (string[0] == '$' && (ft_isalnum(string[1]) || string[1] == '_' || string[1] == '?' || string[1] == '\'' || string[1] == '"'));
	return (string[0] == '$' && (ft_isalnum(string[1]) || string[1] == '_' || string[1] == '?'));
//	return (string != get_end_parameter(string));
}

char	get_current_quote(char *string, char *quote)
{
	if ((*string == '"' || *string == '\'') && *quote == 0)
		*quote = *string;
	else if (*string == *quote)
		*quote = 0;
	return (*quote);
}
