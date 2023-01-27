/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_get_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:19:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 18:19:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_hashmap.h"

static size_t	count_keys(t_hashmap map);
static size_t	insert_map_list_keys(char **keys, t_list *map_list);

char	**hm_get_keys(t_hashmap map)
{
	char				**keys;
	t_hashmap_content	*key;
	t_list				*map_list;
	size_t				map_index;
	size_t				index;

	if (map == NULL)
		return (NULL);
	keys = malloc(sizeof(char *) * (count_keys(map) + 1));
	if (keys == NULL)
		return (NULL);
	map_index = 0;
	index = 0;
	while (index < HASHMAP_ARR_SIZE)
	{
		index += insert_map_list_keys(keys + index, map[index]);
		map_index++;
	}
	keys[index] = NULL;
	return (keys);
}

static size_t	count_keys(t_hashmap map)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (index < HASHMAP_ARR_SIZE)
	{
		count += ft_lstsize(map[index]);
		index++;
	}
	return (count);
}

static size_t	insert_map_list_keys(char **keys, t_list *map_list)
{
	t_hashmap_content	*map_content;
	size_t				count;

	count = 0;
	while (map_list != NULL)
	{
		map_content = map_list->content;
		keys[count] = map_content->target;
		count++;
		map_list = map_list->next;
	}
	return (count);
}