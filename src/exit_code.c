/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:10:16 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 23:09:15 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exit_code.h"
#include "libft.h"
#include "env_variables.h"
#include <sys/wait.h>
#include <stdlib.h>

static int	static_exit_code(int new_exit_code, t_hashmap_content *env_var_ptr);

int	exit_code(int new_exit_code)
{
	return (static_exit_code(new_exit_code, NULL));
}

static int	static_exit_code(int new_exit_code, t_hashmap_content *env_var_ptr)
{
	static t_hashmap_content	*env_var;
	char						*tmp;
	static int					exit_code = 0;

	if (env_var_ptr != NULL)
		env_var = env_var_ptr;
	if (new_exit_code == GET)
		return (exit_code);
	exit_code = new_exit_code;
	tmp = ft_itoa(exit_code);
	if (tmp != NULL)
	{
		free(env_var->content);
		env_var->content = tmp;
	}
	return (exit_code);
}

int	init_exit_code(t_hashmap env_variables)
{
	char	*tmp;

	tmp = ft_strdup("0");
	if (tmp == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, LAST_EXIT_CODE, tmp, &free))
		return (-1);
	static_exit_code(GET, ft_hm_get_elem(env_variables, LAST_EXIT_CODE));
	return (0);
}

int	get_pid_exit_code(int pid_exit_code)
{
	if (WIFEXITED(pid_exit_code))
		return (exit_code(WEXITSTATUS(pid_exit_code)));
	return (exit_code(130));
}
