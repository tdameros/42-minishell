/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:58:31 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 18:05:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static int	get_path(t_token *command, char **path_strs, char **paths);

int	command_is_in_path(t_token *command, t_hashmap env_variables)
{
	char	**paths;
	char	*path_strs[4];

	paths = ft_split(ft_hm_get_content(env_variables, "PATH"), ':');
	if (paths == NULL)
		return (-1);
	path_strs[1] = "/";
	path_strs[2] = command->args[0];
	path_strs[3] = NULL;
	if (get_path(command, path_strs, paths))
	{
		ft_free_split(paths);
		return (-1);
	}
	ft_free_split(paths);
	return (0);
}

static int	get_path(t_token *command, char **path_strs, char **paths)
{
	size_t	i;

	i = -1;
	while (paths[++i] != NULL)
	{
		path_strs[0] = paths[i];
		command->name = ft_join_strs(path_strs, "");
		if (command->name == NULL)
			return (-1);
		if (access(command->name, F_OK) == 0)
			return (0);
		free(command->name);
	}
	if (ft_strchr(command->args[0], '/') != NULL)
		command->name = ft_strdup(command->args[0]);
	else
		command->name = ft_strdup(COMMAND_NOT_FOUND);
	if (command->name == NULL)
		return (-1);
	return (0);
}
