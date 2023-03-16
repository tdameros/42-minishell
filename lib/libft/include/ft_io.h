/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_io.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:00:10 by vfries            #+#    #+#             */
/*   Updated: 2023/02/06 08:46:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IO_H
# define FT_IO_H

# include <unistd.h>

char	*get_next_line_multi_fd(int fd);
char	*get_next_line(int fd);

void	ft_print_position_in_code(const char *file, const char *function,
			const int line);
void	ft_putchar_fd(const char c, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(const char *s, int fd);

// Bonus
void	ft_putstr(const char *s);
int		ft_printf(const char *format, ...);

#endif
