/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:39:50 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 18:45:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "lexer.h"

bool	is_absolute_path(t_token *command, t_hashmap env_variables)
{
	if (ft_hm_get_content(env_variables, "PATH") == NULL)
		return (true);
	return (ft_strrchr(command->args[0], '/') != NULL);
}

int	command_is_absolute_path(t_token *command)
{
	command->type = EXECUTABLE;
	command->name = ft_strdup(command->args[0]);
	if (command->name == NULL)
		return (-1);
	return (0);
}
