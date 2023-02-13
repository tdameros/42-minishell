/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 23:35:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"
#include "exit_code.h"
#include "get_cursor_x_pos.h"
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <sys/wait.h>

static void	signal_handler(int sig);

static void	interactive_signal_handler(int sig);

void	init_interactive_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &interactive_signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	interactive_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
//	rl_on_new_line();
//	rl_replace_line("", 0);
	exit(130);
}


void	init_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	signal_handler(int sig)
{
	int			wait_exit_code;
	const pid_t	pid = waitpid(-1, &wait_exit_code, WUNTRACED);

	if (sig != SIGINT || (pid == -1 && WIFEXITED(wait_exit_code)))
		return ;
	exit_code(130);
	if (pid == -1)
	{
		rl_replace_line("", 0);
		ft_putstr("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (get_cursor_x_pos() > 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}