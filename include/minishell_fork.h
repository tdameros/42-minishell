/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fork.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 07:02:28 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 07:03:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FORK_H
# define MINISHELL_FORK_H

# include "libft.h"

extern t_list	*g_forks;

pid_t	minishell_fork(void);

#endif
