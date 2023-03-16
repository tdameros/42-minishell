/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:41:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/06 16:02:11 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "builtins.h"
#include "exit_code.h"

int	export(char **args, t_hashmap env_variables)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if (print_export(env_variables) < 0)
		{
			print_error("export", args[index], strerror(errno));
			return (set_exit_code(1));
		}
	}
	else
		return (set_exit_code(export_variables(args + index, env_variables)));
	return (set_exit_code(0));
}
