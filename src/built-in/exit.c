/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/15 00:28:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "minishell_struct.h"
#include "exit_code.h"
#include "built_in.h"
#include "terminal.h"

int	exit_builtin(char **args, t_minishell *minishell)
{
	long long	status;

	write(1, "exit\n", 5);
	if (args[1] == NULL)
	{
		terminal_restore(minishell->termios_save);
		exit(0);
	}
	if (args[2] != NULL)
	{
		print_error("exit", NULL, "too many arguments");
		return (exit_code(1));
	}
	terminal_restore(minishell->termios_save);
	errno = 0;
	status = ft_atoll(args[1]);
	if (errno == ERANGE || errno == EINVAL)
	{
		print_error("exit", args[1], "numeric argument required");
		exit(2);
	}
	exit(status);
}
