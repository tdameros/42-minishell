/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:05:49 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 14:03:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "ft_linked_list.h"
#include <stdlib.h>

void	free_token(void *token)
{
	ft_free_split(((t_token *)token)->args);
	free(((t_token *)token)->name);
	if (((t_token *)token)->files != NULL)
		ft_lstclear(&((t_token *)token)->files, &free_token);
	free(token);
}
