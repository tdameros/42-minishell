/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:18:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 00:18:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

int	env(char **args, t_hashmap env_variables)
{
	print_env_variables(env_variables);
	return (0);
}
