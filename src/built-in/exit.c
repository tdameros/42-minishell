/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 17:26:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "built_in.h"

void	exit_builtin(char **args, t_hashmap env_variables)
{
	unsigned char	status;

	write(1, "exit\n", 5);
	if (args[1] == NULL)
		exit(0);
	if (!ft_is_number(args[1]))
	{
		print_error("exit", args[1], "numeric argument required");
		exit(2);
	}
	if (args[2] != NULL)
	{
		print_error("exit", NULL, "too many arguments");
		return (update_last_exit_code(env_variables, 1));
	}
	status = ft_atoi(args[1]);
	exit(status);
}
