/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:10:16 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 17:35:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exit_code.h"
#include "libft.h"
#include <sys/wait.h>

int	exit_code(int new_exit_code)
{
	static int	exit_code = 0;

	if (new_exit_code != GET)
		exit_code = new_exit_code;
	return (exit_code);
}

int	get_pid_exit_code(int pid_exit_code)
{
	if (WIFEXITED(pid_exit_code))
		return (exit_code(WEXITSTATUS(pid_exit_code)));
	return (exit_code(130));
}
