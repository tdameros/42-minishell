/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/05 23:09:31 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exit_code.h"
#include "builtins.h"

int	env(char **args, t_hashmap env_variables)
{
	(void ) args;
	print_env_variables(env_variables);
	return (set_exit_code(0));
}
