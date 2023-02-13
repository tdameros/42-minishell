/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:17:54 by vfries            #+#    #+#             */
/*   Updated: 2023/02/07 00:05:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stdlib.h>
#include "readline/readline.h"
#include <sys/wait.h>
#include <errno.h>
#include "error.h"

#define HERE_DOC_PROMPT "> "

static int	add_here_doc(t_list **here_docs, char *limiter);
static int	get_input(t_list **input_lst, char *limiter);
static int	add_input(t_list **input_lst, int *pipe_fd);
static void	close_pipe(int *fd);
static int	get_forked_input(int *pipe_fd, char *limiter);

int	get_here_docs(char *command, t_list **here_docs)
{
	t_list	*tokens_list;
	t_list	*tokens;
	t_token	*token;
	t_token	*next_token;
	int		return_code;

	tokens_list = get_tokens(command);
	if (tokens_list == NULL)
		return (-1);
	tokens = tokens_list;
	return_code = 0;
	while (tokens->next != NULL)
	{
		token = tokens->content;
		next_token = tokens->next->content;
		if (token->operator == HERE_DOC)
			return_code = add_here_doc(here_docs, next_token->name);
		if (return_code != 0)
		{
			ft_lstclear(&tokens_list, &free_token);
			return (return_code);
		}
		tokens = tokens->next;
	}
	ft_lstclear(&tokens_list, &free_token);
	return (0);
}

static int	add_here_doc(t_list **here_docs, char *limiter)
{
	t_list	*input;
	t_list	*new_node;
	int		return_code;

	input = NULL;
	return_code = get_input(&input, limiter);
	if (return_code != 0)
	{
		ft_lstclear(&input, &free);
		return (return_code);
	}
//	ft_printf("here1");
	new_node = ft_lstnew(input);
	if (new_node == NULL)
	{
		ft_lstclear(&input, &free);
		return (1);
	}
	ft_lstadd_front(here_docs, new_node);
	return (0);
}

static int	get_input(t_list **input_lst, char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	// TODO Make this work with ctrl c handling
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (close_pipe(pipe_fd), 1);
	else if (pid == 0)
		exit(get_forked_input(pipe_fd, limiter));
	if (waitpid(pid, &exit_code, 0) < 0)
		return (close_pipe(pipe_fd), 1);
	exit_code = WEXITSTATUS(exit_code);
	if (exit_code == 130 || exit_code == 1)
		return (close_pipe(pipe_fd), exit_code);
	return (add_input(input_lst, pipe_fd));
}

static int	get_forked_input(int *pipe_fd, char *limiter)
{
	char	*input;

	init_interactive_signal_handling();
	if (errno != 0)
		return (close_pipe(pipe_fd), 1);
	input = readline("> ");
	while (input != NULL && ft_strcmp(input, limiter) != 0)
	{
		ft_putstr_fd(input, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		if (errno != 0)
			return (free(input), close_pipe(pipe_fd), 1);
		free(input);
		input = readline("> ");
	}
	free(input);
	close_pipe(pipe_fd);
	if (errno != 0)
		return (1);
	return (0);
}

static int	add_input(t_list **input_lst, int *pipe_fd)
{
	char	*input;
	t_list	*new_node;

	if (close(pipe_fd[1]) < 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	input = get_next_line(pipe_fd[0]);
	if (input == NULL)
		print_error(NULL, "warning", "here-document delimited by end-of-file");
	while (input != NULL)
	{
		new_node = ft_lstnew(input);
		if (new_node == NULL)
			return (1);
		ft_lstadd_front(input_lst, new_node);
		input = get_next_line(pipe_fd[0]);
	}
	close(pipe_fd[0]);
	return (0);
}

static void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
