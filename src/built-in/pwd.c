/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/05 23:09:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"
#include "exit_code.h"
#include "built_in.h"

int	pwd(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
//	current_path[100] = 0;
	if (current_path == NULL)
	{
		print_error("pwd", NULL, strerror(errno));
		return (exit_code(1));
	}
	ft_printf("%s\n", current_path);
	free(current_path);
	return (exit_code(0));
}
