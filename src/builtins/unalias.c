/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:10:44 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/22 22:10:49 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exit_code.h"
#include "error.h"

int	unalias(char **args, t_hashmap alias)
{
	size_t	index;
	int		exit;

	index = 1;
	exit = 0;
	while (args[index] != NULL)
	{
		if (ft_hm_get_elem(alias, args[index]) == NULL)
		{
			print_error("unalias", args[index], "not found");
			exit = 1;
		}
		else
			ft_hm_delete_elem(alias, args[index], free);
		index++;
	}
	return (set_exit_code(exit));
}
