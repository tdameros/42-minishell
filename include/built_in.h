/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 17:27:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "env_variables.h"

void	echo(char **args, t_hashmap env_variables);
void	cd(char **args, t_hashmap env_variables);
void	pwd(t_hashmap env_variables);
void	export(char **args, t_hashmap env_variables);
void	env(char **args, t_hashmap env_variables);
void	unset(char **args, t_hashmap env_variables);
void	exit_builtin(char **args, t_hashmap env_variables);

void	update_last_exit_code(t_hashmap env_variables, int exit_code);

#endif
