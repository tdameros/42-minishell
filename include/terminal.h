/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 04:42:52 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 05:22:30 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <termios.h>

int	terminal_restore(struct termios termios_save);
int	terminal_save(struct termios *termios_save);
int	terminal_disable_ctrl_backslash_output(void);

#endif
