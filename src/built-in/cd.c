/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/05 23:09:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "exit_code.h"
#include "error.h"
#include "built_in.h"

static int	change_directory(char *path, t_hashmap env_variables);

int	cd(char **args, t_hashmap env_variables)
{
	char	*path;

	if (args[1] != NULL && args[2] != NULL)
	{
		print_error("cd", NULL, "too many arguments");
		return (exit_code(1));
	}
	if (args[1] == NULL)
		path = ft_hm_get_content(env_variables, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error("cd", NULL, "HOME not set");
		return (exit_code(1));
	}
	return (exit_code(change_directory(path, env_variables)));
}

static int	change_directory(char *path, t_hashmap env_variables)
{
	char	*old_path;

	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
		return (1);
	if (chdir(path) < 0)
	{
		print_error("cd", path, strerror(errno));
		free(old_path);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (old_path == NULL)
		return (free(old_path), 1);
	if (ft_hm_add_elem(env_variables, "OLDPWD", old_path, free) < 0)
		return (free(old_path), free(path), 1);
	if (ft_hm_add_elem(env_variables, "PWD", path, free) < 0)
		return (free(old_path), free(path), 1);
	return (0);
}
