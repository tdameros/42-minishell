/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 06:42:49 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 07:00:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*g_forks = NULL;

static pid_t	on_fork(t_list *new_elem);
static pid_t	on_main(t_list *new_elem);

pid_t	minishell_fork(void)
{
	pid_t	*pid;
	t_list	*new_elem;

	pid = malloc(sizeof(pid_t));
	new_elem = ft_lstnew(pid);
	if (new_elem == NULL || pid == NULL)
	{
		free(new_elem);
		free(pid);
		return (-1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		free(new_elem);
		free(pid);
		return (-1);
	}
	if (*pid == 0)
		return (on_fork(new_elem));
	return (on_main(new_elem));
}

static pid_t	on_fork(t_list *new_elem)
{
	const pid_t	pid = *(pid_t *)(new_elem->content);

	free(new_elem->content);
	free(new_elem);
	ft_lstclear(&g_forks, &free);
	return (pid);
}

static pid_t	on_main(t_list *new_elem)
{
	ft_lstadd_front(&g_forks, new_elem);
	return (*(pid_t *)(new_elem->content));
}
