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

static char	*get_git_branch(t_hashmap env_variables);

int	add_git_branch(t_list **prompt, t_hashmap env_variables,
				bool colored_prompt)
{
	char	*git_branch;

	git_branch = get_git_branch(env_variables);
	if (git_branch == NULL)
		return (0);
	if (colored_prompt == false)
	{
		if (add_elem_to_prompt(prompt, git_branch) < 0)
			return (-1);
		return (add_elem_to_prompt(prompt, ft_strdup(" ")));
	}
	if (add_elem_to_prompt(prompt, ft_strdup(BLACK_HIGH_INTENSITY)) < 0)
		return (-1);
	if (add_elem_to_prompt(prompt, git_branch) < 0)
		return (-1);
	return (add_elem_to_prompt(prompt, ft_strdup(" ")));
}

static char	*get_git_branch(t_hashmap env_variables)
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
