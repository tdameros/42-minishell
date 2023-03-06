/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_result.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:40:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/15 11:40:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

static int	execute_forked_command_in_pipe(char *path, char **args, char **envp, int *fd);
static char	*get_str_in_pipe(int *fd);
static char	*get_str_in_fd(int fd);
static void	close_pipe(int *fd);

char	*get_command_result(char *path, char **args, char **envp)
{
	int		fd[2];
	int		pid;
	int		exit_code;

	if (pipe(fd) < 0)
		return (NULL);
	pid = fork();
	if (pid < 0)
		return (close_pipe(fd), NULL);
	else if (pid == 0)
		exit(execute_forked_command_in_pipe(path, args, envp, fd));
	if (waitpid(pid, &exit_code, 0) < 0)
		return (close_pipe(fd), NULL);
	exit_code = WEXITSTATUS(exit_code);
	if (exit_code != 0)
		return (close_pipe(fd), NULL);
	return (get_str_in_pipe(fd));
}

static int	execute_forked_command_in_pipe(char *path, char **args, char **envp, int *fd)
{
	if (close(fd[0]) < 0)
	{
		close(fd[1]);
		return (1);
	}
	if (close(STDERR_FILENO) < 0)
	{
		close(fd[1]);
		return (1);
	}
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		close(fd[1]);
		close(fd[0]);
		return (1);
	}
	if (close(fd[1]) < 0)
		return (1);
	execve(path, args, envp);
	return (1);
}

static char	*get_str_in_pipe(int *fd)
{
	char	*result;

	if (close(fd[1]) < 0)
	{
		close(fd[0]);
		return (NULL);
	}
	result = get_str_in_fd(fd[0]);
	if (close(fd[0]) < 0)
		return (NULL);
	return (result);
}

static char	*get_str_in_fd(int fd)
{
	char	*result;
	char	*line;
	char	*tmp;

	result = get_next_line(fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_strjoin(result, line);
		free(result);
		free(line);
		if (tmp == NULL)
			return (NULL);
		result = tmp;
		line = get_next_line(fd);
	}
	return (result);
}

static void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
