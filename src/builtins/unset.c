/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:07:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 15:07:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exit_code.h"
#include "error.h"

static	bool	is_valid_key(char *key);

int	unset(char **args, t_hashmap env_variables)
{
	size_t	index;
	int		exit;

	index = 1;
	exit = 0;
	while (args[index] != NULL)
	{
		if (!is_valid_key(args[index]))
		{
			print_error("unset", args[index], "not a valid identifier");
			exit = 1;
		}
		else
			ft_hm_delete_elem(env_variables, args[index], free);
		index++;
	}
	return (set_exit_code(exit));
}

static	bool	is_valid_key(char *key)
{
	size_t	index;

	index = 0;
	if (!ft_isalpha(key[index]) && key[index] != '_')
		return (false);
	while (key[index] != '\0')
	{
		if (!ft_isalnum(key[index]) && key[index] != '_')
			return (false);
		index++;
	}
	return (true);
}
