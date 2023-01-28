/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 00:18:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"

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
		return (1);
	}
	status = ft_atoi(args[1]);
	exit(status);
}
