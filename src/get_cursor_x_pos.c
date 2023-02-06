/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_x_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:42:04 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 13:26:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include "error.h"

#define BUFFER_SIZE 30
#define CURSOR_ERROR "Failed to get cursor position"

static int	get_cursor_pos(char *buf);
static void	prep_termios_structs(struct termios *term_tmp,
				struct termios *term_backup);

/// @brief 		Returns cursor position on terminal colons, starts at 1
/// @return 	if ret > 0 -> ret == cursor position,
/// 			if ret == 0 -> stdin / out / err is not a terminal,
/// 			if ret < 0 -> error
int	get_cursor_x_pos(void)
{
	char	buf[BUFFER_SIZE];
	int		i;
	int		multiplier;
	int		cursor_x_pos;

	if (isatty(STDERR_FILENO) == 0 || isatty(STDOUT_FILENO) == 0
		|| isatty(STDIN_FILENO) == 0)
		return (0);
	i = get_cursor_pos(buf) - 1;
	if (i < 2)
		return (-1);
	cursor_x_pos = 0;
	multiplier = 1;
	while (i >= 0 && buf[i] != ';')
	{
		cursor_x_pos = cursor_x_pos + (buf[i] - '0') * multiplier;
		multiplier *= 10;
		i--;
	}
	if (i < 0)
		return (-1);
	return (cursor_x_pos);
}

static int	get_cursor_pos(char *buf)
{
	int				i;
	char			tmp_char;
	struct termios	term_tmp;
	struct termios	term_backup;

	prep_termios_structs(&term_tmp, &term_backup);
	write(STDOUT_FILENO, "\033[6n", 4);
	i = 0;
	tmp_char = 0;
	while (i < BUFFER_SIZE && tmp_char != 'R')
	{
		if (read(STDIN_FILENO, &tmp_char, 1) < 1)
		{
			tcsetattr(STDERR_FILENO, TCSANOW, &term_backup);
			return (-1);
		}
		buf[i] = tmp_char;
		i++;
	}
	tcsetattr(STDERR_FILENO, TCSANOW, &term_backup);
	if (i >= BUFFER_SIZE)
		return (-1);
	buf[i] = 0;
	return (i - 1);
}

static void	prep_termios_structs(struct termios *term_tmp,
				struct termios *term_backup)
{
	tcgetattr(STDERR_FILENO, term_backup);
	tcgetattr(STDERR_FILENO, term_tmp);
	term_tmp->c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDERR_FILENO, TCSANOW, term_tmp);
}
