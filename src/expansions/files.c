/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:02:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/09 02:04:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "expansions.h"

static int	file_expansion(t_token *file, t_hashmap env_variables);
static int	set_ambiguous_file(t_token *file);

int	apply_files_expansion(t_list *files, t_hashmap env_variables)
{
	while (files != NULL)
	{
		if (file_expansion(files->content, env_variables) < 0)
			return (-1);
		files = files->next;
	}
	return (0);
}

static int	file_expansion(t_token *file, t_hashmap env_variables)
{
	t_list		*tokens;
	t_expansion	*expansion;

	errno = 0;
	tokens = get_str_expansion(file->name, env_variables);
	if (errno != 0)
		return (-1);
	if (tokens == NULL || tokens->next != NULL)
	{
		ft_lstclear(&tokens, free_expansion);
		return (set_ambiguous_file(file));
	}
	free(file->name);
	expansion = tokens->content;
	file->name = expansion->content;
	ft_lstclear(&tokens, free);
	return (0);
}

static int	set_ambiguous_file(t_token *file)
{
	free(file->name);
	file->name = NULL;
	return (0);
}
