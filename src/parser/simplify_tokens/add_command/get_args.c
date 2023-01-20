/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:37 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 09:02:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include <stdlib.h>

char	**get_args_strs(t_list **args, t_list **parsed_tokens)
{
	char	**args_strs;
	int		i;

	args_strs = malloc(sizeof(char *) * (ft_lstsize(*args) + 2));
	if (args_strs == NULL)
	{
		ft_lstclear(args, &free_token);
		return (NULL);
	}
	args_strs[0] = ((t_token *)(*parsed_tokens)->content)->name;
	((t_token *)(*parsed_tokens)->content)->name = NULL;
	i = 1;
	while (*args != NULL)
	{
		args_strs[i] = ((t_token *)(*args)->content)->name;
		((t_token *)(*args)->content)->name = NULL;
		*args = ft_lst_get_next_free_current(*args, &free_token);
		i++;
	}
	args_strs[i] = NULL;
	return (args_strs);
}
