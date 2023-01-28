/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fork.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:02:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 01:02:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FORK_H
# define MINISHELL_FORK_H

# include "libft.h"

extern t_list	*g_forks;

pid_t	minishell_fork(void);

#endif