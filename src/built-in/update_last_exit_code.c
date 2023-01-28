/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_exit_code.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:18:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 17:19:47 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

void	update_last_exit_code(t_hashmap env_variables, int exit_code)
{
	*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = exit_code;
}
