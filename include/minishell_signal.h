/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:49:49 by vfries            #+#    #+#             */
/*   Updated: 2023/02/23 02:20:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

// execution_fork.c
pid_t	execution_fork(void);

// fork_signal_handling.c
int		signal_init_fork_handling(void);

// general_signal_handling.c
int		signal_init_handling_outside_execution(void);
int		signal_init_handling_inside_execution(void);

// interactive_signal_handling.c
int		init_interactive_signal_handling(void);
int		init_interactive_fork_signal_handling(void);

// pipes_signal_handling.c
int		signal_init_handling_pipes(void);

#endif
