/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:07:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 00:07:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_hashmap.h"

int	unset(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	while (args[index] != NULL)
	{
		if (ft_hm_delete_elem(env_variables, args[index], free) < 0)
			return (1);
		index++;
	}
	return (0);
}
