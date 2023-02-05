/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/05 16:18:56 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "exit_code.h"
#include "built_in.h"

int	env(char **args, t_hashmap env_variables)
{
	(void ) args;
	print_env_variables(env_variables);
	return (exit_code(0));
}
