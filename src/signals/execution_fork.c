/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 23:54:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/08 23:54:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell_signal.h"

pid_t	execution_fork(void)
{
	const pid_t	pid = fork();

	if (pid != 0)
		return (pid);
	signal_init_fork_handling();
	return (pid);
}
