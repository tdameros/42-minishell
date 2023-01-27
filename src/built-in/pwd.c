/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:33:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 17:33:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"

int	pwd(void)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
	{
		print_error("pwd", NULL, strerror(errno));
		return (1);
	}
	ft_printf("%s\n", current_path);
	free(current_path);
	return (0);
}