/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/05 16:19:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "exit_code.h"
#include "built_in.h"

int	exit_builtin(char **args)
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
		return (exit_code(1));
	}
	status = ft_atoi(args[1]);
	exit(status);
}
