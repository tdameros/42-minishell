/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_branch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:40:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/06 01:08:58 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env_variables.h"
#include "prompt.h"

#define GIT_BINARY "/usr/bin/git"

char	*get_git_branch(t_hashmap env_variables)
{
	const char	*command[] = {GIT_BINARY, "branch", "--show-current", NULL};
	char		*git_branch;
	char		*tmp;
	char		**envp;

	envp = get_non_empty_envp(env_variables, GIT_BINARY);
	if (envp == NULL)
		return (NULL);
	git_branch = get_command_result(GIT_BINARY, (char **)command, envp);
	ft_free_split(envp);
	if (git_branch == NULL)
		return (NULL);
	tmp = ft_strtrim(git_branch, "\n");
	free(git_branch);
	git_branch = tmp;
	return (git_branch);
}
