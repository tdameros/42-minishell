/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/15 17:49:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "error.h"
#include "exit_code.h"
#include "terminal.h"
#include "minishell_struct.h"

static void	restore_terminal_and_free_everything(t_minishell *minishell);

int	exit_builtin(char **args, t_minishell *minishell)
{
	long long	status;

	write(1, "exit\n", 5);
	if (args[1] == NULL)
	{
		restore_terminal_and_free_everything(minishell);
		exit(0);
	}
	errno = 0;
	status = ft_atoll(args[1]);
	if (args[2] != NULL && errno != EINVAL)
	{
		print_error("exit", NULL, "too many arguments");
		return (set_exit_code(1));
	}
	if (errno == ERANGE || errno == EINVAL)
	{
		print_error("exit", args[1], "numeric argument required");
		restore_terminal_and_free_everything(minishell);
		exit(2);
	}
	restore_terminal_and_free_everything(minishell);
	exit(status);
}

static void	restore_terminal_and_free_everything(t_minishell *minishell)
{
	terminal_restore(minishell->termios_save);
	free_minishell(minishell);
}
