/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:19:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/06 23:19:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <error.h>
#include "expansions.h"

void	free_path(t_path *path)
{
	free(path->relative);
	free(path->absolute);
}

int	is_wildcard(char *pattern)
{
	char	quote;

	quote = 0;
	while (*pattern != '\0')
	{
		if (quote == 0 && (*pattern == '\'' || *pattern == '"'))
			quote = *pattern;
		else if (quote != 0 && quote == *pattern)
			quote = 0;
		else if (quote == 0 && (*pattern == '*' || *pattern == '?'))
			return (1);
		pattern++;
	}
	return (0);
}

ssize_t	size_with_wildcards_args(char **arguments)
{
	size_t	size;
	t_list	*wildcards_list;

	size = 0;
	while (*arguments != NULL)
	{
		if (is_wildcard(*arguments))
		{
			wildcards_list = get_wildcards_list(*arguments);
			if (errno != 0)
				return (-1);
			if (wildcards_list == NULL)
				size += 1;
			else
				size += ft_lstsize(wildcards_list);
			ft_lstclear(&wildcards_list, free);
		}
		else
			size += 1;
		arguments++;
	}
	return (size);
}
