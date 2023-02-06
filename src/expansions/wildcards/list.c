/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:50:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 22:50:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <error.h>
#include <dirent.h>
#include "expansions.h"

t_list	*get_wildcards_list(char *path, char *pattern)
{
	t_list	*wildcards;
	t_path	wildcards_path;

	errno = 0;
	wildcards = NULL;
	wildcards_path.absolute = ft_strdup(path);
	if (ft_strcmp(path, "/") == 0)
		wildcards_path.relative = ft_strdup("/");
	else
		wildcards_path.relative = ft_strdup("");
	if (wildcards_path.relative == NULL || wildcards_path.absolute == NULL)
	{
		free_path(&wildcards_path);
		return (NULL);
	}
	if (add_match_in_list(&wildcards, wildcards_path, pattern) < 0)
		ft_lstclear(&wildcards, free);
	return (wildcards);
}
