/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_replacing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:16:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/31 19:16:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "libft.h"
#include <stdlib.h>

int	replace_alias(char **args, t_hashmap alias_variables)
{
	char	*alias_content;

	alias_content = ft_hm_get_content(alias_variables, args[0]);
	if (alias_content != NULL)
	{
		alias_content = ft_strdup(alias_content);
		if (alias_content == NULL)
			return (-1);
		free(args[0]);
		args[0] = alias_content;
	}
	return (0);
}
