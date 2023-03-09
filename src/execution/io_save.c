/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:59:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:33:17 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exit_code.h"

int	save_io(char *command_name, int *io_save)
{
	int	ret;

	ret = 0;
	io_save[0] = dup(STDIN_FILENO);
	if (io_save[0] < 0)
	{
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	io_save[1] = dup(STDOUT_FILENO);
	if (io_save[1] < 0)
	{
		if (close(io_save[0]) < 0)
			print_error(command_name, BUILTIN_CLOSE_FAILED, get_error());
		print_error(command_name, BUILTIN_DUP_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	return (ret);
}

int	close_io_save(char *command_name, int *io_save)
{
	int	ret;

	ret = 0;
	if (close(io_save[0]) < 0)
	{
		print_error(command_name, BUILTIN_CLOSE_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	if (close(io_save[1]) < 0)
	{
		print_error(command_name, BUILTIN_CLOSE_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	return (ret);
}

int	restore_io_and_close_io_save(int *io_save, char *command_name)
{
	int	ret;

	ret = 0;
	if (dup2(io_save[0], STDIN_FILENO) < 0)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	if (dup2(io_save[1], STDOUT_FILENO) < 0)
	{
		print_error(command_name, BUILTIN_DUP2_FAILED, get_error());
		exit_code(-1);
		ret = -1;
	}
	if (close_io_save(command_name, io_save) < 0)
	{
		exit_code(-1);
		ret = -1;
	}
	return (ret);
}
