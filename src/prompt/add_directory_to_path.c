/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_directory_to_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 21:38:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/08 21:38:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "prompt.h"

static char	*get_current_working_directory(t_hashmap env_variables);

int	add_directory_path(t_list **prompt, t_hashmap env_variables,
				bool colored_prompt)
{
	char	*cwd;
	char	*result;

	cwd = get_current_working_directory(env_variables);
	if (cwd == NULL)
		return (-1);
	if (colored_prompt)
		result = ft_strjoin_three(BLUE_HIGH_INTENSITY, cwd, " ");
	else
		result = ft_strjoin(cwd, " ");
	free(cwd);
	return (add_elem_to_prompt(prompt, result));
}

static char	*get_current_working_directory(t_hashmap env_variables)
{
	char	*home_dir;
	size_t	home_dir_len;
	char	*cwd;

	if (ft_hm_get_content(env_variables, "PWD") != NULL)
		cwd = ft_strdup(ft_hm_get_content(env_variables, "PWD"));
	else
		cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ft_strdup("."));
	home_dir = ft_hm_get_content(env_variables, "HOME");
	if (home_dir != NULL)
		home_dir_len = ft_strlen(home_dir);
	if (home_dir != NULL && *home_dir != '\0' && *cwd != '\0'
		&& ft_strncmp(cwd, home_dir, home_dir_len) == 0)
	{
		cwd[0] = '~';
		ft_strlcpy(cwd + 1, cwd + home_dir_len, ft_strlen(cwd) + 1 - 1);
	}
	return (cwd);
}
