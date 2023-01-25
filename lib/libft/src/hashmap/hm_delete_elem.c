/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_delete_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/25 17:06:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include <stdlib.h>

int	ft_hm_delete_elem(t_hashmap map, char *target, void (*del)(void *))
{
	t_list	*cursor;

	cursor = map[ft_hm_get_index(target)];
	while (cursor != NULL
		   && ft_strcmp(((t_hashmap_content *)cursor->content)->target, target)
			  != 0)
		cursor = cursor->next;
	if (cursor == NULL)
		return (-1);
	:W

}
