/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 03:14:57 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 15:43:51 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_variables.h"

void	print_env_variables(t_hashmap env_variables)
{
	int					i;
	t_list				*cursor;
	t_hashmap_content	*hm_content;

	i = HASHMAP_ARR_SIZE;
	while (i-- > 0)
	{
		cursor = env_variables[i];
		while (cursor != NULL)
		{
			hm_content = cursor->content;
			if (hm_content->content != NULL
				&& ft_strcmp(hm_content->target, LAST_EXIT_CODE))
				ft_printf("%s=%s\n", hm_content->target, hm_content->content);
			cursor = cursor->next;
		}
	}
}
