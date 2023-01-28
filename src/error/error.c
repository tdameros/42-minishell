/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/27 17:01:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_error(char *command, char *context, char *error)
{
	if (context != NULL)
		ft_printf("minishell: %s: %s: %s\n", command, context, error);
	else
		ft_printf("minishell: %s: %s\n", command, error);
}