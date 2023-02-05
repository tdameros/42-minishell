/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/05 16:21:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "env_variables.h"

int	cd(char **args, t_hashmap env_variables);
int	echo(char **args);
int	env(char **args, t_hashmap env_variables);
int	exit_builtin(char **args);
int	export(char **args, t_hashmap env_variables);
int	pwd(void);
int	unset(char **args, t_hashmap env_variables);

#endif
