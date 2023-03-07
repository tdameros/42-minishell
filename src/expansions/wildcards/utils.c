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
#include <sys/stat.h>
#include <error.h>
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

int	add_wildcard_with_space(char *content, int type, t_list **tokens)
{
	t_list	*new_node;

	new_node = create_expansion_node(content, type);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_front(tokens, new_node);
	return (0);
}
