/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_signal_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:25:59 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:53:54 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <sys/wait.h>

#include "error.h"
#include "exit_code.h"
#include "get_cursor_x_pos.h"

static void	signal_handler_outside_execution(int sig);
static void	signal_handler_inside_execution(int sig);

int	signal_init_handling_outside_execution(void)
{
	struct sigaction	action;

	action.sa_handler = &signal_handler_outside_execution;
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

static void	signal_handler_outside_execution(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_replace_line("", 0);
	ft_putstr("\n");
	rl_on_new_line();
	rl_redisplay();
	exit_code(130);
}

int	signal_init_handling_inside_execution(void)
{
	struct sigaction	action;

	action.sa_handler = &signal_handler_inside_execution;
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

static void	signal_handler_inside_execution(int sig)
{
	pid_t	pid;

	errno = 0;
	pid = waitpid(-1, NULL, 0);
	if (errno == ECHILD || pid == -1)
		return ;
	if (sig == SIGQUIT)
	{
		if (get_cursor_x_pos() > 1)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		exit_code(131);
	}
	else if (sig == SIGINT)
	{
		if (get_cursor_x_pos() > 1)
			ft_putchar_fd('\n', STDERR_FILENO);
		exit_code(130);
	}
}
