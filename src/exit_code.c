/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:10:16 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:55:05 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "exit_code.h"
#include "env_variables.h"

int	g_exit_code = 0;

int	set_exit_code(int new_exit_code)
{
	g_exit_code = new_exit_code;
	return (new_exit_code);
}

int	get_exit_code(void)
{
	return (g_exit_code);
}

int	update_exit_code_in_env_variables(t_hashmap env_variables)
{
	char	*str_exit_code;

	str_exit_code = ft_itoa(get_exit_code());
	if (str_exit_code == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, LAST_EXIT_CODE, str_exit_code, &free) < 0)
	{
		free(str_exit_code);
		return (-1);
	}
	return (0);
}
