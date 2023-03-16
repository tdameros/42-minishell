/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:10:27 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 23:58:38 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODE_H
# define EXIT_CODE_H

# include <limits.h>
# include "libft.h"

//	exit_code.c
int	set_exit_code(int new_exit_code);
int	get_exit_code(void);
int	update_exit_code_in_env_variables(t_hashmap env_variables);

#endif
