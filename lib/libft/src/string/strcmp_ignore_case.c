/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp_ignore_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:49:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/07 19:49:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ignore_case(char c);

int	ft_strcmp_ignore_case(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (ignore_case(*s1) != ignore_case(*s2))
			return (ignore_case(*s1) - ignore_case(*s2));
		s1++;
		s2++;
	}
	return (ignore_case(*s1) - ignore_case(*s2));
}

static char	ignore_case(char c)
{
//	if (ft_isalpha(c))
		return (ft_tolower(c));
//	return (255);
}
