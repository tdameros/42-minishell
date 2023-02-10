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

#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
#include "expansions.h"

static int	search_match(char **pattern, char **string, char *quote);
static int	is_start_or_end_quote(char *string, char *quote);
static int	search_match_after_star(char **pattern, char **string);
static int	get_index_end_pattern(char *pattern);

int	is_match(char *pattern, char *string)
{
	char	quote;
	int		search_match_result;
	char	*pattern_without_quotes;

	quote = 0;
	if (pattern[0] != '.' && string[0] == '.')
		return (false);
	while (*string != '\0' && *pattern != '\0')
	{
		search_match_result = search_match(&pattern, &string, &quote);
		if (search_match_result == 0 || search_match_result == 1)
			return (search_match_result);
	}
	if (quote != 0 && *pattern == quote)
		pattern++;
	pattern_without_quotes = strdup_without_quote(pattern);
	pattern = pattern_without_quotes;
	if (pattern_without_quotes == NULL)
		return (0);
	while (*pattern == '*')
		pattern++;
	if (ft_strlen(pattern) != 0)
		return (free(pattern_without_quotes), 0);
	free(pattern_without_quotes);
	return (*string == '\0');
}

static int	search_match(char **pattern, char **string, char *quote)
{
	if (is_start_or_end_quote(*pattern, quote))
		*pattern += 1;
	else if (**pattern == '?' && *quote == 0)
	{
		*pattern += 1;
		*string += 1;
	}
	else if (**pattern == '*' && *(*pattern + 1) == '\0' && *quote == 0)
		return (1);
	else if (**pattern == '*' && *(*pattern + 1) == '*' && *quote == 0)
		*pattern += 1;
	else if (**pattern == '*' && *quote == 0)
	{
		if (search_match_after_star(pattern, string) == 0)
			return (0);
	}
	else
	{
		if (**string != **pattern)
			return (0);
		*pattern += 1;
		*string += 1;
	}
	return (-1);
}

static int	is_start_or_end_quote(char *string, char *quote)
{
	if (*string == *quote && *quote != 0)
	{
		*quote = 0;
		return (1);
	}
	else if (*quote == 0 && (*string == '\'' || *string == '"'))
	{
		*quote = *string;
		return (1);
	}
	return (0);
}

static int	search_match_after_star(char **pattern, char **string)
{
	char	*sub_pattern;
	char	*tmp;

	(*pattern)++;
	while (**pattern == '?')
		(*pattern)++;
	tmp = ft_substr(*pattern, 0, get_index_end_pattern(*pattern));
	if (tmp == NULL)
		return (0);
	sub_pattern = strdup_without_quote(tmp);
	free(tmp);
	if (sub_pattern == NULL)
		return (0);
	*string = ft_strrstr(*string, sub_pattern);
	if (*string == NULL)
	{
		free(sub_pattern);
		return (0);
	}
	*string += ft_strlen(sub_pattern);
	free(sub_pattern);
	*pattern += get_index_end_pattern(*pattern);
	return (1);
}

static int	get_index_end_pattern(char *pattern)
{
	int		index;
	char	quote;

	index = 0;
	quote = 0;
	is_start_or_end_quote(pattern, &quote);
	while (pattern[index] != '\0'
		&& !(quote == 0 && (pattern[index] == '*' || pattern[index] == '?')))
	{
		index++;
		is_start_or_end_quote(pattern, &quote);
	}
	return (index);
}
