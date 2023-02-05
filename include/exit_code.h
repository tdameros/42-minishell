/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:10:27 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 23:06:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODE_H
# define EXIT_CODE_H

# include <limits.h>
# include "libft.h"

# define GET INT_MIN

int	exit_code(int new_exit_code);
int	init_exit_code(t_hashmap env_variables);
int	get_pid_exit_code(int pid_exit_code);

#endif
