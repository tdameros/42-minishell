/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:46:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/07 17:46:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <error.h>
#include "expansions.h"
#include "libft.h"

static void		fill_tab_with_list(char **tab, t_list *list);
static ssize_t	fill_tab_with_wildcards(char **tab, char *argument);
static ssize_t	fill_tab_if_is_wildcard(char **tab, char *argument);

char	**duplicate_argument_with_wildcards(char **argument)
{
	ssize_t	count;
	ssize_t	result;
	char	**new_args;

	count = size_with_wildcards_args(argument);
	if (count == -1)
		return (NULL);
	new_args = ft_calloc(count + 1, sizeof(*new_args));
	if (new_args == NULL)
		return (NULL);
	count = 0;
	while (*argument != NULL)
	{
		result = fill_tab_with_wildcards(new_args + count, *argument);
		if (result < 0)
		{
			ft_free_split(new_args);
			return (NULL);
		}
		count += result;
		argument++;
	}
	return (new_args);
}

static ssize_t	fill_tab_with_wildcards(char **tab, char *argument)
{
	if (is_wildcard(argument))
		return (fill_tab_if_is_wildcard(tab, argument));
	else
	{
		argument = ft_strdup(argument);
		if (argument == NULL)
			return (-1);
		*tab = argument;
	}
	return (1);
}

static ssize_t	fill_tab_if_is_wildcard(char **tab, char *argument)
{
	char	**wildcards_tab;
	ssize_t	count;

	count = 0;
	wildcards_tab = get_wildcards_tab(argument);
	if (errno != 0)
		return (-1);
	if (wildcards_tab == NULL)
	{
		argument = ft_strdup(argument);
		if (argument == NULL)
			return (-1);
		*tab = argument;
		return (1);
	}
	while (wildcards_tab[count] != NULL)
	{
		*tab = wildcards_tab[count];
		tab++;
		count++;
	}
	free(wildcards_tab);
	return (count);
}

char	**get_wildcards_tab(char *pattern)
{
	char	**new_tab;
	t_list	*wildcards_list;
	size_t	size;

	wildcards_list = get_wildcards_list(pattern);
	if (wildcards_list == NULL)
		return (NULL);
	size = ft_lstsize(wildcards_list);
	new_tab = malloc(sizeof(*new_tab) * (size + 1));
	if (new_tab == NULL)
	{
		ft_lstclear(&wildcards_list, free);
		return (NULL);
	}
	fill_tab_with_list(new_tab, wildcards_list);
	new_tab[size] = NULL;
	ft_lstclear(&wildcards_list, NULL);
	if (ft_msort_str_ignore_case(new_tab, 0, size - 1) < 0)
	{
		ft_free_split(new_tab);
		return (NULL);
	}
	return (new_tab);
}

static void	fill_tab_with_list(char **tab, t_list *list)
{
	size_t	index;

	index = 0;
	while (list != NULL)
	{
		tab[index] = list->content;
		index++;
		list = list->next;
	}
}
