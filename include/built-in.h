/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/25 15:28:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

int	echo(char **args);
int	cd(char **args, t_hashmap env_variables);
int	pwd(void);
int	export(char **args, t_hashmap env_variables);
int	env(char **args, t_hashmap env_variables);
int	unset(char **args, t_hashmap env_variables);
int	exit_builtin(char **args);

#endif
