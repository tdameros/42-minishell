/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 05:32:11 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:01:12 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int	add_path(t_token *command, t_hashmap env_variables)
{
	if (command->args == NULL || command->args[0] == NULL)
		return (0);
	command->builtin = is_builtin(command->args[0]);
	if (command->builtin != (enum e_builtin) - 1)
	{
		command->type = BUILTIN;
		return (0);
	}
	if (is_absolute_path(command, env_variables))
	{
		if (command_is_absolute_path(command))
			return (-1);
		return (0);
	}
	if (command_is_in_path(command, env_variables))
		return (-1);
	return (0);
}
