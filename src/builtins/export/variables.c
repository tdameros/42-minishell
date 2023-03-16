/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:10:56 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/22 22:10:59 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "builtins.h"

int	export_variables(char **args, t_hashmap env_variables)
{
	size_t	index;
	int		return_code;
	int		result;

	index = 0;
	return_code = 0;
	while (args[index] != NULL)
	{
		result = export_variable(args[index], env_variables);
		if (result == 0)
		{
			print_error("export", args[index], "not a valid identifier");
			return_code = 1;
		}
		else if (result < 0)
		{
			print_error("export", args[index], strerror(errno));
			return (1);
		}
		index++;
	}
	return (return_code);
}
