/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/05 19:18:53 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "env_variables.h"
# include "minishell_struct.h"

int		cd(char **args, t_hashmap env_variables);
char	*get_cleaned_path(const char *path);
int		echo(char **args);
int		env(char **args, t_hashmap env_variables);
int		exit_builtin(char **args, t_minishell *minishell);
int		export(char **args, t_hashmap env_variables);
int		print_export(t_hashmap env_variables);
int		export_variables(char **args, t_hashmap env_variables);
int		export_variable(char *variable, t_hashmap env_variables);
int		pwd(t_hashmap env_variables);
int		unset(char **args, t_hashmap env_variables);

#endif
