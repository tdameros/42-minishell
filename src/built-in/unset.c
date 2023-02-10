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
#include "ft_hashmap.h"
#include "exit_code.h"
#include "built_in.h"

int	unset(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		ft_hm_delete_elem(env_variables, args[index], free);
		index++;
	}
	return (exit_code(0));
}
