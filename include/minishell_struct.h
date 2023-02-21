/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:52:27 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 21:52:38 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

# include <termios.h>
# include "libft.h"

typedef struct s_minishell
{
	t_hashmap		env_variables;
	t_list			*tokens;
	t_list			*here_docs;
	struct termios	termios_save;
}	t_minishell;

#endif
