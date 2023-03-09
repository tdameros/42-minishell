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

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env_variables.h"
# include "minishell_struct.h"

//	alias/alias.c
int		alias(char **args, t_hashmap alias);

//	alias/get_all_aliases.c
char	**get_all_aliases(t_hashmap aliases);

//	cd/cd.c
int		cd(char **args, t_hashmap env_variables);

//	cd/get_cleaned_path.c
char	*get_cleaned_path(const char *path);

//	cd/handle_cwd_doesnt_exist.c
int		handle_cwd_doesnt_exist(char *path, t_hashmap env_variables);

//	export/export.c
int		export(char **args, t_hashmap env_variables);

//	export/print.c
int		print_export(t_hashmap env_variables);

//	export/variable.c
int		export_variable(char *variable, t_hashmap env_variables);

//	export/variables.c
int		export_variables(char **args, t_hashmap env_variables);

//	echo.c
int		echo(char **args);

//	env.c
int		env(char **args, t_hashmap env_variables);

//	exit.c
int		exit_builtin(char **args, t_minishell *minishell);

//	pwd.c
int		pwd(t_hashmap env_variables);

//	unset.c
int		unset(char **args, t_hashmap env_variables);

#endif
