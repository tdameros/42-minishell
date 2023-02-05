/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:49:49 by vfries            #+#    #+#             */
/*   Updated: 2023/02/04 23:56:45 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

extern int	g_sigint_status;

void	init_main_signal_handling(void);
void	init_execution_signal_handling(void);
void	update_last_exit_sigint(t_hashmap env_variables);

#endif
