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

#include <stdlib.h>
#include "libft.h"
#include "env_variables.h"

void	update_last_exit_code(t_hashmap env_variables, int exit_code)
{
	char	*str_exit_code;

	str_exit_code = ft_itoa(exit_code);
	if (str_exit_code == NULL)
		return;
	ft_hm_add_elem(env_variables, LAST_EXIT_CODE, str_exit_code, free);
}
