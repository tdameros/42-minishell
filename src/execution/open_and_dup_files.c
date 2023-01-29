/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_dup_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:51:38 by vfries            #+#    #+#             */
/*   Updated: 2023/01/29 01:00:07 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"
#include "env_variables.h"
#include <fcntl.h>

static int	open_and_dup(t_token *file);
static int	open_file(t_token *file);

int	open_and_dup_files(t_list *files, t_hashmap env_variables,
		t_list *here_docs)
{
	t_token	*token;

	while (files != NULL)
	{
		token = files->content;
		//if (token->operator == HERE_DOC && handle_here_docs())
		//	{
		//\		*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = 1;
		//		return (-1);
		//	}
		if (token->operator == HERE_DOC)
		{
			(void)here_docs; // TODO
			//TODO if return -1 set $? to 1
		}
		else if (open_and_dup(token))
		{
			*(int *)ft_hm_get_content(env_variables, LAST_EXIT_CODE) = 1;
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
	if (ret == -1)
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
