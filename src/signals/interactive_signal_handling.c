/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_signal_handling.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:26:05 by vfries            #+#    #+#             */
/*   Updated: 2023/02/23 17:26:06 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "error.h"

static void	interactive_signal_handler(int sig);
static void	interactive_fork_signal_handler(int sig);

int	init_interactive_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &interactive_signal_handler;
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

static void	interactive_signal_handler(int sig)
{
	(void)sig;
}

int	init_interactive_fork_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &interactive_fork_signal_handler;
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

static void	interactive_fork_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(130);
}
