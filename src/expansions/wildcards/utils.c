/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:19:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 23:19:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "expansions.h"

void	free_path(t_path *path)
{
	free(path->relative);
	free(path->absolute);
}

int	is_wildcard(char *pattern)
{
	return (ft_strchr(pattern, '*') != NULL
		|| ft_strchr(pattern, '?') != NULL);
}
