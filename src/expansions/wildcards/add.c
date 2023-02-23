/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:19:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 23:19:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <error.h>
#include "expansions.h"

static int	add_simple_match_in_list(t_list **path_list, t_path path,
				char *pattern);
static int	search_dir_match(t_list **path_list, t_path path, char *pattern);
static int	add_dir_match_in_list(t_list **path_list, t_path path,
				char *pattern, struct dirent *file);

int	add_match_in_list(t_list **path_list, t_path path, char *pattern)
{
	errno = 0;
	if (ft_strchr(pattern, '/') == NULL)
	{
		if (add_simple_match_in_list(path_list, path, pattern) < 0)
			return (free_path(&path), -1);
	}
	else
	{
		if (search_dir_match(path_list, path, pattern) < 0)
			return (free_path(&path), -1);
	}
	free_path(&path);
	return (0);
}

static int	add_simple_match_in_list(t_list **path_list,
										t_path path, char *pattern)
{
	DIR				*dir;
	struct dirent	*file;
	char			*new_relative_path;

	dir = opendir(path.absolute);
	if (dir == NULL)
	{
		errno = 0;
		return (0);
	}
	file = readdir(dir);
	while (file != NULL)
	{
		if (is_match(pattern, file->d_name))
		{
			new_relative_path = ft_strjoin(path.relative, file->d_name);
			ft_lstadd_front(path_list, ft_lstnew(new_relative_path));
			if (errno != 0)
				return (free(new_relative_path), closedir(dir) - 1);
		}
		file = readdir(dir);
	}
	errno = 0;
	return (closedir(dir));
}

static int	search_dir_match(t_list **path_list, t_path path, char *pattern)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(path.absolute);
	if (dir == NULL)
	{
		errno = 0;
		return (0);
	}
	file = readdir(dir);
	while (file != NULL)
	{
		if (add_dir_match_in_list(path_list, path, pattern, file) < 0)
			return (closedir(dir) - 1);
		file = readdir(dir);
	}
	errno = 0;
	return (closedir(dir));
}

static int	add_dir_match_in_list(t_list **path_list, t_path path,
									char *pattern, struct dirent *file)
{
	char	*slash;
	t_path	new_path;

	slash = ft_strchr(pattern, '/');
	*slash = '\0';
	if (ft_isdir(path.absolute, file->d_name)
		&& is_match(pattern, file->d_name))
	{
		new_path.absolute = ft_strjoin_three(path.absolute, "/", file->d_name);
		new_path.relative = ft_strjoin_three(path.relative, file->d_name, "/");
		if (new_path.relative == NULL || new_path.absolute == NULL)
			return (free_path(&new_path), -1);
		if (ft_strlen(ft_skip_char(slash + 1, '/')) == 0)
		{
			ft_lstadd_front(path_list, ft_lstnew(new_path.relative));
			if (errno != 0)
				return (free_path(&new_path), -1);
			free(new_path.absolute);
		}
		else
			if (add_match_in_list(path_list, new_path, slash + 1) < 0)
				return (-1);
	}
	*slash = '/';
	return ((errno == 0) - 1);
}
