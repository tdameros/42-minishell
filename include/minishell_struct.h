/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 05:12:31 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 18:41:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <termios.h>
# include "libft.h"

typedef struct s_minishell
{
	t_hashmap		env_variables;
	struct termios	termios_save;
}	t_minishell;

#endif
