/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:09:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/05 23:09:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exit_code.h"

static bool	is_n_flag(char *arg);

int	echo(char **args)
{
	int		index;
	int		return_code;
	bool	n_flag;

	index = 1;
	return_code = 0;
	n_flag = is_n_flag(args[index]);
	while (is_n_flag(args[index]))
		index++;
	while (args[index] != NULL)
	{
		if (args[index + 1] != NULL)
			return_code = ft_printf("%s ", args[index]);
		else
			return_code = ft_printf("%s", args[index]);
		if (return_code < 0)
			return (set_exit_code(-1));
		index++;
	}
	if (!n_flag)
		return_code = ft_printf("\n");
	if (return_code < 0)
		return (set_exit_code(-1));
	return (set_exit_code(0));
}

static bool	is_n_flag(char *arg)
{
	int	index;

	if (arg == NULL || ft_strncmp(arg, "-n", 2) != 0)
		return (false);
	index = 2;
	while (arg[index] != '\0')
	{
		if (arg[index] != 'n')
			return (false);
		index++;
	}
	return (true);
}
