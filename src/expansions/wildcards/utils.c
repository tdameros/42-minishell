/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdamerose@student.42lyon.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:37:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 17:37:57 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

#include "expansions.h"

bool	ft_isdir(char *path, char *file_name)
{
	struct stat	*stat_buf;
	bool		result;
	char		*file;

	stat_buf = malloc(sizeof(*stat_buf));
	if (stat_buf == NULL)
		return (false);
	file = ft_strjoin_three(path, "/", file_name);
	if (file == NULL)
		return (free(stat_buf), false);
	if (stat(file, stat_buf) < 0)
	{
		errno = 0;
		result = false;
	}
	else
		result = S_ISDIR(stat_buf->st_mode);
	free(stat_buf);
	free(file);
	return (result);
}

void	free_path(t_path *path)
{
	free(path->relative);
	free(path->absolute);
}

bool	has_wildcard_in_pattern(t_list *pattern)
{
	t_expansion	*expansion;

	while (pattern != NULL)
	{
		expansion = pattern->content;
		if (expansion->type == STAR)
			return (true);
		pattern = pattern->next;
	}
	return (false);
}
