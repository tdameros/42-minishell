/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dots_from_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:35:44 by vfries            #+#    #+#             */
/*   Updated: 2023/03/05 19:27:48 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static t_list		*init_lst(void);
static const char	*handle_dot_dot(t_list **lst, const char *path);
static const char	*handle_directory(t_list **lst, const char *path);

char	*get_cleaned_path(const char *path)
{
	t_list	*lst;
	char	*cleaned_path;

	lst = init_lst();
	if (lst == NULL)
		return (NULL);
	path = ft_skip_char(path, '/');
	while (*path != '\0')
	{
		if (ft_strncmp("../", path, 3) == 0 || ft_strcmp("..", path) == 0)
			path = handle_dot_dot(&lst, path);
		else if (ft_strncmp("./", path, 2) == 0 || ft_strcmp(".", path) == 0)
			path += 1;
		else
			path = handle_directory(&lst, path);
		if (path == NULL)
		{
			ft_lstclear(&lst, &free);
			return (NULL);
		}
		path = ft_skip_char(path, '/');
	}
	cleaned_path = ft_lst_join_strs(ft_lst_reverse(&lst));
	ft_lstclear(&lst, &free);
	return (cleaned_path);
}

static t_list	*init_lst(void)
{
	t_list	*lst;
	char	*str;

	str = ft_strdup("/");
	lst = ft_lstnew(str);
	if (str == NULL || lst == NULL)
	{
		free(str);
		free(lst);
		return (NULL);
	}
	return (lst);
}

static const char	*handle_dot_dot(t_list **lst, const char *path)
{
	if ((*lst)->next != NULL)
		ft_lst_get_next_free_current(lst, &free);
	return (path + 2);
}

static const char	*handle_directory(t_list **lst, const char *path)
{
	const char	*slash = ft_strchr(path, '/');
	char		*directory;
	t_list		*new_node;

	if (slash == NULL)
		directory = ft_strdup(path);
	else
		directory = ft_substr(path, 0, slash - path + 1);
	new_node = ft_lstnew(directory);
	if (directory == NULL || new_node == NULL)
	{
		free(directory);
		free(new_node);
		return (NULL);
	}
	ft_lstadd_front(lst, new_node);
	if (slash == NULL)
		return (path + ft_strlen(path));
	return (slash);
}
