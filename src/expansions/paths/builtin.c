/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 01:39:18 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:01:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_builtin	is_builtin(char *command_name)
{
	if (ft_strcmp(command_name, "echo") == 0)
		return (ECHO_CMD);
	if (ft_strcmp(command_name, "cd") == 0)
		return (CD);
	if (ft_strcmp(command_name, "pwd") == 0)
		return (PWD);
	if (ft_strcmp(command_name, "export") == 0)
		return (EXPORT);
	if (ft_strcmp(command_name, "unset") == 0)
		return (UNSET);
	if (ft_strcmp(command_name, "env") == 0)
		return (ENV);
	if (ft_strcmp(command_name, "exit") == 0)
		return (EXIT);
	if (ft_strcmp(command_name, "alias") == 0)
		return (ALIAS);
	if (ft_strcmp(command_name, "unalias") == 0)
		return (UNALIAS);
	return (-1);
}
