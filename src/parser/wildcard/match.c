/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:44:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/24 15:44:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <dirent.h>

int	get_index_end_pattern(char *pattern);
int	is_match(char *pattern, char *string);

char	**get_wildcards(char *pattern, char *path)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(path);
	file = readdir(dir);
	while (file != NULL)
	{
		if (is_match(pattern, file->d_name))
			ft_printf("%s\n", file->d_name);
		file = readdir(dir);
	}
	return (NULL);
}

int	is_match(char *pattern, char *string)
{
	char *sub_pattern;

	while (*string != '\0' && *pattern != '\0')
	{
		if (*pattern == '?')
		{
			pattern++;
			string++;
		}
		else if (*pattern == '*' && *(pattern + 1) == '\0')
			return (1);
		else if (*pattern == '*' && *(pattern + 1) == '*')
			pattern++;
		else if (*pattern == '*')
		{
			pattern++;
			while (*pattern == '?')
				pattern++;
			sub_pattern = ft_substr(pattern, 0, get_index_end_pattern(pattern));
			string = ft_strnstr(string, sub_pattern, ft_strlen(string));
			free(sub_pattern);
			if (string == NULL)
				return (0);
			string += get_index_end_pattern(pattern);
			pattern += get_index_end_pattern(pattern);
		}
		else
		{
			if (*string != *pattern)
				return (0);
			string++;
			pattern++;
		}
	}
	return (*string == '\0');
}

int	get_index_end_pattern(char *pattern)
{
	int	index;

	index = 0;
	while (pattern[index] != '\0' && pattern[index] != '*')
		index++;
	return (index);
}