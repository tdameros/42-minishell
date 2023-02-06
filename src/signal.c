/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 11:14:07 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"
#include "exit_code.h"
#include "get_cursor_x_pos.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

static void	main_signal_handler(int sig);
static void	execution_signal_handler(int sig);

void	init_main_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &main_signal_handler;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	main_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	exit_code(1);
	rl_replace_line("", 0);
	ft_putstr("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	init_execution_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &execution_signal_handler;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	execution_signal_handler(int sig)
{
	int	get_cursor_x_pos_ret;

	if (sig != SIGINT)
		return ;
	exit_code(130);
	get_cursor_x_pos_ret = get_cursor_x_pos();
	if (get_cursor_x_pos_ret != 1 && get_cursor_x_pos_ret > 0)
		ft_putstr("\n");
}
