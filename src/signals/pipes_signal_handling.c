/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_signal_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:26:15 by vfries            #+#    #+#             */
/*   Updated: 2023/02/23 17:26:16 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "error.h"
#include "exit_code.h"

static void	signal_handler_pipes(int sig);

int	signal_init_handling_pipes(void)
{
	struct sigaction	action;

	action.sa_handler = &signal_handler_pipes;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &action, NULL) < 0)
	{
		print_error(NULL, "sigaction() failed", get_error());
		return (-1);
	}
	if (sigaction(SIGQUIT, &action, NULL) < 0)
	{
		print_error(NULL, "sigaction() failed", get_error());
		return (-1);
	}
	return (0);
}

static void	signal_handler_pipes(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		exit_code(131);
	}
	else if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		exit_code(130);
	}
}
