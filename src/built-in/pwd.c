/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 17:26:41 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"
#include "built_in.h"

void	pwd(t_hashmap env_variables)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
	{
		print_error("pwd", NULL, strerror(errno));
		return (update_last_exit_code(env_variables, 1));
	}
	ft_printf("%s\n", current_path);
	free(current_path);
	return (update_last_exit_code(env_variables, 0));
}
