/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:57:50 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 16:09:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H

# include "ft_hashmap.h"

t_hashmap	get_env_variables(char **envp);
char		**get_envp(t_hashmap env_variables);
void		print_env_variables(t_hashmap env_variables);

#endif
