/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:14:57 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 03:16:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_env_variables(t_hashmap env_variables)
{
	int		i;
	t_list	*cursor;

	i = HASHMAP_ARR_SIZE;
	while (i-- > 0)
	{
		cursor = env_variables[i];
		while (cursor != NULL)
		{
			ft_printf("%s=%s\n",
				((t_hashmap_content *)cursor->content)->target,
				((t_hashmap_content *)cursor->content)->content);
			cursor = cursor->next;
		}
	}
}
