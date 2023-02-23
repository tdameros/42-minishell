/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/23 02:20:21 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"
#include "error.h"
#include "exit_code.h"
#include "get_cursor_x_pos.h"
#include "sys/wait.h"
#include "terminal.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	interactive_signal_handler(int sig);
static void	signal_handler_outside_execution(int sig);
static void	signal_handler_inside_execution(int sig);
static void	signal_handler_pipes(int sig);
static void	interactive_signal_handler_interactive(int sig);

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
	if (sig != SIGINT)
		return ;
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(130);
}

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

int	init_interactive_signal_handling_interactive(void)
{
	struct sigaction	action;

	action.sa_handler = &interactive_signal_handler_interactive;
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

static void	interactive_signal_handler_interactive(int sig)
{
	(void)sig;
}
