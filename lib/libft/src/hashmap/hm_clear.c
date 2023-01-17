/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:33:35 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 16:42:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashmap.h"
#include <stdlib.h>

static void	free_hashmap_list(t_list *lst, void (*del)(void *));

/// @brief 		Frees all elements of a hashmap and sets it to NULL
/// @param map 	Hashmap to free
/// @param del 	Fonction to free hashmap content
void	ft_hm_clear(t_hashmap *map, void (*del)(void *))
{
	size_t	i;

	i = 0;
	while (i < HASHMAP_ARR_SIZE)
	{
		free_hashmap_list((*map)[i], del);
		i++;
	}
	free(*map);
	*map = NULL;
}

static void	free_hashmap_list(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	free_hashmap_list(lst->next, del);
	if (lst->content != NULL)
	{
		if (((t_hashmap_content *)lst->content)->content != NULL)
			del(((t_hashmap_content *)lst->content)->content);
		free(((t_hashmap_content *)lst->content)->target);
	}
	free(lst->content);
	free(lst);
}
