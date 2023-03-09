/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cwd_doesnt_exist.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:58:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/08 21:58:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"
#include "error.h"

static int	change_dir(char *path, t_hashmap env_variables);

int	handle_cwd_doesnt_exist(char *path, t_hashmap env_variables)
{
	char	*pwd;
	char	*new_pwd;
	char	*cleaned_new_pwd;

	pwd = ft_hm_get_content(env_variables, "PWD");
	if (pwd == NULL)
	{
		print_error("cd", path, "No such file or directory");
		return (1);
	}
	if (ft_hm_add_elem(env_variables, "OLDPWD", pwd, &free) < 0)
		return (perror("cd: failed to update OLDPWD"), -1);
	if (pwd[ft_strlen(pwd) - 1] != '/')
		new_pwd = ft_strjoin_three(pwd, "/", path);
	else
		new_pwd = ft_strjoin(pwd, path);
	if (new_pwd == NULL || ft_hm_add_elem(env_variables, "PWD", new_pwd, NULL))
		return (perror("cd: failed to update PWD"), free(new_pwd), -1);
	cleaned_new_pwd = get_cleaned_path(new_pwd);
	if (cleaned_new_pwd == NULL)
		return (perror("cd: error retrieving cleaned_new_pwd"), -1);
	return (change_dir(cleaned_new_pwd, env_variables));
}

static int	change_dir(char *path, t_hashmap env_variables)
{
	if (chdir(path) < 0)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
		perror("getcwd: cannot access parent directories");
		free(path);
	}
	else if (ft_hm_add_elem(env_variables, "PWD", path, &free) < 0)
	{
		perror("cd: failed to update PWD");
		free(path);
		return (-1);
	}
	return (0);
}
