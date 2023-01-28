/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:07:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 17:26:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_hashmap.h"
#include "built_in.h"

void	unset(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (ft_hm_delete_elem(env_variables, args[index], free) < 0)
			return (update_last_exit_code(env_variables, 1));
		index++;
	}
	return (update_last_exit_code(env_variables, 0));
}
