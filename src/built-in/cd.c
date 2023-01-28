/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 17:26:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "built_in.h"

void	cd(char **args, t_hashmap env_variables)
{
	char	*path;
	char	*old_path;

	// TODO: tilde
	if (args[1] != NULL && args[2] != NULL)
	{
		print_error("cd", NULL, "too many arguments");
		return (update_last_exit_code(env_variables, 1));
	}
	if (args[1] == NULL)
		path = ft_hm_get_content(env_variables, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error("cd", NULL, "HOME not set");
		return (update_last_exit_code(env_variables, 1));
	}
	old_path = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		print_error("cd", path, strerror(errno));
		free(old_path);
		return (update_last_exit_code(env_variables, 1));
	}
	path = getcwd(NULL, 0);
	ft_hm_add_elem(env_variables, "OLDPWD", old_path, free);
	ft_hm_add_elem(env_variables, "PWD", path, free);
	return (update_last_exit_code(env_variables, 0));
}
