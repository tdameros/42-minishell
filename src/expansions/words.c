/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:15:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/29 17:15:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_split_args(char **args);
static ssize_t	insert_split_args(char *arg, char **dest_args);

char	**split_args(char **args)
{
	char	**new_args;

	new_args = ft_calloc(count_split_args(args) + 1, sizeof(*new_args));
	if (new_args == NULL)
		return (NULL);
	while (*args != NULL)
	{
		if (insert_split_args(*args, new_args) < 0)
		{
			ft_free_split(new_args);
			return (NULL);
		}
		args++;
	}
	return (new_args);
}

static size_t	count_split_args(char **args)
{
	size_t	count;

	count = 0;
	while (*args != NULL)
	{
		count += ft_count_args_after_split_unless_quotes(*args);
		args++;
	}
	return (count);
}

static ssize_t	insert_split_args(char *arg, char **dest_args)
{
	char	**split_args;
	size_t	index;
	size_t	index_dest;

	split_args = ft_split_unless_in_quotes(arg);
	if (split_args == NULL)
		return (-1);
	index = 0;
	index_dest = ft_split_size(dest_args);
	while (split_args[index] != NULL)
	{
		dest_args[index_dest] = split_args[index];
		index++;
		index_dest++;
	}
	free(split_args);
	return (0);
}
