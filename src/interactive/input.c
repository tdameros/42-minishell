/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:32:35 by vfries            #+#    #+#             */
/*   Updated: 2023/02/24 15:32:40 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "error.h"
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "get_here_docs.h"
#include "minishell_signal.h"
#include "interactive.h"

static int	get_input(char **input, t_minishell *minishell);
static int	get_forked_input(int *pipe_fd);
static int	read_input(int *pipe_fd, char **input);
static int	return_input_error(int return_code, char **command);

int	get_input_command(char **command, char *join, t_minishell *minishell)
{
	char	*new_input;
	char	*new_command;
	int		return_code;

	return_code = get_input(&new_input, minishell);
	if (return_code != 0)
		return (return_input_error(return_code, command));
	new_command = ft_strjoin_three(*command, join, new_input);
	free(*command);
	if (new_command != NULL && ft_strlen(new_input) > 0)
	{
		return_code = get_here_docs_if_valid_syntax(new_input, new_command,
				minishell);
		if (return_code != 0)
		{
			*command = new_command;
			return (free(new_input), return_code);
		}
	}
	*command = new_command;
	return (free(new_input), *command == NULL);
}

static int	get_input(char **input, t_minishell *minishell)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	if (pipe(pipe_fd) < 0)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close_pipe(pipe_fd), 1);
	else if (pid == 0)
	{
		exit_code = get_forked_input(pipe_fd);
		free_minishell(minishell);
		exit(exit_code);
	}
	if (waitpid(pid, &exit_code, 0) < 0)
		return (close_pipe(pipe_fd), 1);
	exit_code = WEXITSTATUS(exit_code);
	if (exit_code == 130 || exit_code == 1)
		return (close_pipe(pipe_fd), exit_code);
	return (read_input(pipe_fd, input));
}

static int	get_forked_input(int *pipe_fd)
{
	char	*input;

	if (init_interactive_fork_signal_handling() < 0)
		return (close_pipe(pipe_fd), 1);
	input = readline("> ");
	errno = 0;
	if (input != NULL && ft_strlen(input) == 0)
		ft_putstr_fd(" ", pipe_fd[1]);
	ft_putstr_fd(input, pipe_fd[1]);
	if (errno != 0)
		return (free(input), close_pipe(pipe_fd), 1);
	free(input);
	close_pipe(pipe_fd);
	if (errno != 0)
		return (1);
	return (0);
}

static int	read_input(int *pipe_fd, char **input)
{
	char	*tmp;

	if (close(pipe_fd[1]) < 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	*input = get_next_line(pipe_fd[0]);
	if (close(pipe_fd[0]) < 0)
		return (1);
	if (*input == NULL)
	{
		print_error("syntax error", NULL, "unexpected end of file");
		return (2);
	}
	tmp = ft_strtrim(*input, " ");
	free(*input);
	if (tmp == NULL)
		return (1);
	*input = tmp;
	return (0);
}

static int	return_input_error(int return_code, char **command)
{
	if (return_code == 2)
	{
		free(*command);
		*command = NULL;
	}
	return (return_code);
}
