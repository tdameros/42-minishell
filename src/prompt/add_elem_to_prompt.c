/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elem_to_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:42:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/08 21:42:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

int	add_elem_to_prompt(t_list **prompt, char *elem)
{
	t_list	*new_node;

	if (elem == NULL)
		return (-1);
	new_node = ft_lstnew(elem);
	if (new_node == NULL)
	{
		free(elem);
		return (-1);
	}
	ft_lstadd_front(prompt, new_node);
	return (0);
}
