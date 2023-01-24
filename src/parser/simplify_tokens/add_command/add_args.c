/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:54:37 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 06:10:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"
#include <stdlib.h>

static char	**get_args_strs(t_list **args);

int	add_args(t_token *token, t_list **args)
{
	if (args == NULL)
		return (0);
	token->args = get_args_strs(args);
	if (token->args == NULL)
		return (-1);
	return (0);
}

static char	**get_args_strs(t_list **args)
{
	char	**args_strs;
	t_token	*token;
	int		size;

	size = ft_lstsize(*args);
	args_strs = malloc(sizeof(char *) * (size + 1));
	if (args_strs == NULL)
	{
		ft_lstclear(args, &free_token);
		return (NULL);
	}
	args_strs[size--] = NULL;
	while (*args != NULL)
	{
		token = (*args)->content;
		args_strs[size] = token->name;
		token->name = NULL;
		ft_lst_get_next_free_current(args, &free_token);
		size--;
	}
	return (args_strs);
}
