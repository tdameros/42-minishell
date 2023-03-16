/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:50:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/09 02:02:14 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <error.h>

#include "expansions.h"

static int	cmp_match(void *content1, void *content2);

t_list	*get_wildcards_list(t_list *pattern)
{
	t_list	*wildcards;
	t_path	wildcards_path;

	errno = 0;
	wildcards = NULL;
	if (is_slash_token(pattern))
	{
		wildcards_path.relative = ft_strdup("/");
		wildcards_path.absolute = ft_strdup("/");
		pattern = skip_slash_token(pattern);
	}
	else
	{
		wildcards_path.absolute = getcwd(NULL, 0);
		wildcards_path.relative = ft_strdup("");
	}
	if (wildcards_path.relative == NULL || wildcards_path.absolute == NULL)
		return (free_path(&wildcards_path), NULL);
	if (add_match_in_list(&wildcards, wildcards_path, pattern) < 0)
		ft_lstclear(&wildcards, free);
	ft_lst_sort(wildcards, cmp_match);
	return (wildcards);
}

static int	cmp_match(void *content1, void *content2)
{
	t_expansion	*expansion1;
	t_expansion	*expansion2;

	expansion1 = content1;
	expansion2 = content2;
	return (ft_strcmp(expansion1->content, expansion2->content));
}
