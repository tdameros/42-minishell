/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishellrc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 01:44:27 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:56:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

#include "error.h"
#include "execute_single_line_command.h"

static int	open_minishellrc(t_hashmap env_variables);
static void	remove_new_line(char *line);

void	run_minishellrc(t_minishell *minishell)
{
	const int	fd = open_minishellrc(minishell->env_variables);
	char		*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		remove_new_line(line);
		execute_single_line_command(minishell, line);
		free(line);
		line = get_next_line(fd);
	}
}

static int	open_minishellrc(t_hashmap env_variables)
{
	char	*join[3];
	char	*minishellrc_path;
	int		fd;

	join[0] = ft_hm_get_content(env_variables, "HOME");
	if (join[0] == NULL)
		return (-2);
	join[1] = ".minishellrc";
	join[2] = NULL;
	minishellrc_path = ft_join_strs(join, "/");
	if (minishellrc_path == NULL)
	{
		print_error(NULL, "Failed to run .minishellrc", get_error());
		return (-2);
	}
	fd = open(minishellrc_path, O_RDONLY);
	free(minishellrc_path);
	return (fd);
}

static void	remove_new_line(char *line)
{
	char	*new_line;

	new_line = ft_strchr(line, '\n');
	if (new_line != NULL)
		*new_line = '\0';
}
