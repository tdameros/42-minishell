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

t_list	*get_wildcards_list(char *pattern)
{
	t_list	*wildcards;
	t_path	wildcards_path;

	errno = 0;
	wildcards = NULL;
	if (pattern[0] == '/')
	{
		wildcards_path.relative = ft_strdup("/");
		wildcards_path.absolute = ft_strdup("/");
		pattern = ft_skip_char(pattern, '/');
	}
	else
	{
		wildcards_path.absolute = getcwd(NULL, 0);
		wildcards_path.relative = ft_strdup("");
	}
	if (wildcards_path.relative == NULL || wildcards_path.absolute == NULL)
		return (free_path(&wildcards_path), NULL);
	if (add_match_in_list(&wildcards, wildcards_path, pattern) < 0)
		ft_lstclear(&wildcards, free);
	return (wildcards);
}
