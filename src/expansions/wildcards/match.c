/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:47:23 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 02:02:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static bool	is_hidden_file(t_list *wildcard, char *string);
static bool	is_wildcard_pattern(t_list *wildcard);
static int	get_wildcard_pattern(t_list *wildcard);
static int	search_match(t_list **wildcards, char **string);

int	is_wildcard_match(t_list *wildcards, char *string)
{
	t_expansion	*expansion;

	if (is_hidden_file(wildcards, string))
		return (0);
	while (is_wildcard_pattern(wildcards))
	{
		expansion = wildcards->content;
		if (expansion->type == STAR && !is_wildcard_pattern(wildcards->next))
			return (1);
		if (search_match(&wildcards, &string) < 0)
			return (0);
		wildcards = wildcards->next;
	}
	return (*string == '\0');
}

static bool	is_hidden_file(t_list *wildcard, char *string)
{
	t_expansion	*expansion;

	if (wildcard == NULL)
		return (1);
	expansion = wildcard->content;
	if (string[0] == '.' && (expansion->type != WORD
			|| expansion->content[0] != '.'))
		return (1);
	return (0);
}

static bool	is_wildcard_pattern(t_list *wildcard)
{
	t_expansion	*expansion;

	if (wildcard == NULL)
		return (false);
	expansion = wildcard->content;
	if (expansion == NULL)
		return (false);
	return (expansion->type == WORD || expansion->type == STAR);
}

static int	get_wildcard_pattern(t_list *wildcard)
{
	t_expansion	*expansion;

	if (wildcard == NULL)
		return (-1);
	expansion = wildcard->content;
	if (expansion == NULL)
		return (-1);
	return (expansion->type);
}

static int	search_match(t_list **wildcards, char **string)
{
	t_expansion	*expansion;
	t_expansion	*next_expansion;
	t_list		*wildcard;

	wildcard = *wildcards;
	expansion = wildcard->content;
	if (expansion->type == STAR && get_wildcard_pattern(wildcard->next) == WORD)
	{
		next_expansion = wildcard->next->content;
		*string = ft_strrstr(*string, next_expansion->content);
		if (*string == NULL)
			return (-1);
		*string += ft_strlen(next_expansion->content);
		*wildcards = wildcard->next;
	}
	else if (expansion->type == WORD)
	{
		if (ft_strncmp(*string, expansion->content,
				ft_strlen(expansion->content)) != 0)
			return (-1);
		*string += ft_strlen(expansion->content);
	}
	return (0);
}
