/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_dup_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:51:38 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 16:25:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "error.h"
#include "exit_code.h"
#include "env_variables.h"
#include <fcntl.h>

static int	open_and_dup(t_token *file);
static int	open_file(t_token *file);
static int	handle_here_doc(t_token *file, t_list **here_docs);

int	open_and_dup_files(t_list *files, t_list *here_docs)
{
	t_token	*token;

	while (files != NULL)
	{
		token = files->content;
		if (token->operator == HERE_DOC)
		{
			if (handle_here_doc(token, &here_docs))
			{
				exit_code(1);
				return (-1);
			}
		}
		else if (open_and_dup(token))
		{
			exit_code(1);
			return (-1);
		}
		files = files->next;
	}
	return (0);
}

static int	open_and_dup(t_token *file)
{
	int	fd;
	int	ret;

	fd = open_file(file);
	if (fd == -1)
		return (-1);
	if (file->operator == INPUT_REDIRECT)
		ret = dup2(fd, STDIN_FILENO) == -1;
	else
		ret = dup2(fd, STDOUT_FILENO) == -1;
	if (ret)
		print_error(file->name, FILE_DUP2_FAILED, get_error());
	if (close(fd) == -1)
	{
		print_error(file->name, FILE_CLOSE_FAILED, get_error());
		ret = -1;
	}
	return (ret);
}

static int	open_file(t_token *file)
{
	int	fd;

	if (file->operator == INPUT_REDIRECT)
		fd = open(file->name, O_RDONLY);
	else if (file->operator == OUTPUT_REDIRECT)
		fd = open(file->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd = open(file->name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (fd == -1)
		print_error(file->name, NULL, get_error());
	return (fd);
}

static int	handle_here_doc(t_token *file, t_list **here_docs)
{
	const int	fd = read_here_doc(here_docs);

	if (fd == -1)
	{
		print_error(file->name, "here_doc: pipe() failed", get_error());
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_error(file->name, "here_doc: dup2() failed", get_error());
		return (-1);
	}
	return (0);
}
