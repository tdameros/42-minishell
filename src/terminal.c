/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 04:04:09 by vfries            #+#    #+#             */
/*   Updated: 2023/02/15 00:09:02 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include "error.h"

int	terminal_restore(const struct termios *termios_save)
{
	const int	ret = tcsetattr(STDERR_FILENO, TCSANOW, termios_save);

	if (isatty(STDERR_FILENO) == 0 || isatty(STDOUT_FILENO) == 0
		|| isatty(STDIN_FILENO) == 0)
		return (0);
	if (ret < 0)
		print_error(NULL, "Failed to save termios\n", get_error());
	return (ret);
}

int	terminal_save(struct termios *termios_save)
{
	const int	ret = tcgetattr(STDERR_FILENO, termios_save);

	if (isatty(STDERR_FILENO) == 0 || isatty(STDOUT_FILENO) == 0
		|| isatty(STDIN_FILENO) == 0)
		return (0);
	if (ret < 0)
		print_error(NULL, "Failed to restore termios\n", get_error());
	return (ret);
}

int	terminal_disable_ctrl_backslash_output(void)
{
	struct termios	term;

	if (isatty(STDERR_FILENO) == 0 || isatty(STDOUT_FILENO) == 0
		|| isatty(STDIN_FILENO) == 0)
		return (0);
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		print_error(NULL, "Failed to disable SIGQUIT\n", get_error());
		return (-1);
	}
	term.c_cc[VQUIT] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
	{
		print_error(NULL, "Failed to disable SIGQUIT\n", get_error());
		return (-1);
	}
	return (0);
}
