/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:32:11 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 16:56:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

static char	*command_is_builtin(char *command_name, enum e_type *token_type);
static char	*command_is_absolute_path(char **args, enum e_type *token_type);
static char	*command_is_in_path(char *command, t_hashmap env_variables);
static char	*command_is_in_path(char *command, t_hashmap env_variables);
static char	*get_path(char **path_strs, char **paths);

char	*get_command_path(enum e_type *token_type, char **args,
			t_hashmap env_variables)
{
	char	*command_path;

	if (*args == NULL)
		return ((void *)-1);
	command_path = command_is_builtin(*args, token_type);
	if (command_path == (void *)-1)
		return (NULL);
	if (command_path != NULL)
		return (command_path);
	command_path = command_is_absolute_path(args, token_type);
	if (command_path == (void *)-1)
		return (NULL);
	if (command_path != NULL)
		return (command_path);
	return (command_is_in_path(*args, env_variables));
}

static char	*command_is_builtin(char *command_name, enum e_type *token_type)
{
	char	*command_path;

	if (ft_strcmp(command_name, "echo") != 0
		&& ft_strcmp(command_name, "cd") != 0
		&& ft_strcmp(command_name, "pwd") != 0
		&& ft_strcmp(command_name, "export") != 0
		&& ft_strcmp(command_name, "unset") != 0
		&& ft_strcmp(command_name, "env") != 0
		&& ft_strcmp(command_name, "exit") != 0)
		return (NULL);
	*token_type = BUILTIN;
	command_path = ft_strdup(command_name);
	if (command_path == NULL)
		return ((void *)-1);
	return (command_path);
}

static char	*command_is_absolute_path(char **args, enum e_type *token_type)
{
	char	*command_path;
	char	*command;

	if (*args[0] != '.' && *args[0] != '/'
		&& *args[0] != '~')
		return (NULL);
	command = ft_strrchr(*args, '/');
	if (command == NULL)
		return (NULL);
	*token_type = EXECUTABLE;
	command = ft_strdup(command + 1);
	command_path = ft_strdup(*args);
	if (command_path == NULL || command == NULL)
	{
		free(command_path);
		free(command);
		return ((void *)-1);
	}
	free(*args);
	*args = command;
	return (command_path);
}

static char	*command_is_in_path(char *command, t_hashmap env_variables)
{
	char	*path_variable;
	char	**paths;
	char	*path_strs[4];
	char	*command_path;

	path_variable = ft_hm_get_content(env_variables, "PATH");
	if (path_variable == NULL)
		return (ft_strdup(command));
	paths = ft_split(path_variable, ':');
	if (paths == NULL)
		return (NULL);
	path_strs[1] = "/";
	path_strs[2] = command;
	path_strs[3] = NULL;
	command_path = get_path(path_strs, paths);
	ft_free_split(paths);
	if (command_path == NULL)
		return (ft_strdup(command));
	return (command_path);
}

static char	*get_path(char **path_strs, char **paths)
{
	char	*command_path;
	size_t	i;

	i = -1;
	while (paths[++i] != NULL)
	{
		path_strs[0] = paths[i];
		command_path = ft_join_strs(path_strs, "");
		if (command_path != NULL && access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}
