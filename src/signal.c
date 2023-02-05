/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 11:49:43 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "built_in.h"
#include <signal.h>

static void	main_signal_handler(int sig);
static void	execution_signal_handler(int sig);

// TODO might be able to this without a global, needs testing
int	g_sigint_status = 0;

void	init_main_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &main_signal_handler;
	action.sa_mask = 0;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define PROMPT "➜ minishell-1.0$ "

static void	main_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sigint_status = 1;
	rl_replace_line("", 0);
	ft_putstr("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	init_execution_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &execution_signal_handler;
	action.sa_mask = 0;
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	execution_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_sigint_status = 130;
	ft_printf("\n");
}

void	update_last_exit_sigint(t_hashmap env_variables)
{
	if (g_sigint_status == 1)
		update_last_exit_code(env_variables, 1);
	else if (g_sigint_status == 130)
		update_last_exit_code(env_variables, 130);
	g_sigint_status = 0;
}
