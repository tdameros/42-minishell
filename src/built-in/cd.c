/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:25:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 16:25:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"

int	cd(char **args, t_hashmap env_variables)
{
	char	*path;
	char	*old_path;

	if (args[1] == NULL)
		path = ft_hm_get_content(env_variables, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		print_error("cd", NULL, "HOME not set");
		return (1);
	}
	old_path = getcwd(NULL, 0);
	if (chdir(path) < 0)
	{
		print_error("cd", path, strerror(errno));
		free(old_path);
		return (1);
	}
	ft_hm_add_elem(env_variables, "OLDPWD", old_path, free);
	ft_hm_add_elem(path, "PWD", ft_strdup(path), free);
	return (0);
}
