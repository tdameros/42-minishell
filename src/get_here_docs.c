/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:17:54 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 13:56:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdlib.h>

static bool	add_token_here_docs(t_list_i **here_docs_fds, t_list *token);
static bool	add_here_doc(t_list_i **here_docs_fds, char *limiter);
static bool	get_here_doc_input(char *limiter, int pipe_fd[2]);
static bool	add_new_fd(t_list_i **here_docs_fds, int fd);

/// @brief 		Create n number of fd with input from STDIN
///					(n is the number of HERE_DOCs)
/// @param tokens
/// @return 	Returns NULL if they aren't any HERE_DOCs,
///					a with all fds if they are HERE_DOCs,
///					(void *)-1 if a malloc failed
t_list_i	*get_here_docs(t_list *tokens)
{
	t_list_i	*here_docs_fds;

	here_docs_fds = NULL;
	while (tokens != NULL)
	{
		if (add_token_here_docs(&here_docs_fds,
				((t_token *)tokens->content)->files))
		{
			ft_lsti_clear(&here_docs_fds);
			return ((void *)-1);
		}
		tokens = tokens->next;
	}
	return (ft_lsti_reverse(&here_docs_fds));
}

static bool	add_token_here_docs(t_list_i **here_docs_fds, t_list *token)
{
	while (token != NULL)
	{
		if (((t_token *)token->content)->operator == HERE_DOC
			&& add_here_doc(here_docs_fds, ((t_token *)token->content)->name))
			return (true);
		token = token->next;
	}
	return (false);
}

static bool	add_here_doc(t_list_i **here_docs_fds, char *limiter)
{
	int			pipe_fd[2];

	limiter = ft_strjoin(limiter, "\n");
	if (limiter == NULL)
		return (true);
	if (pipe(pipe_fd) == -1)
	{
		free(limiter);
		return (true);
	}
	if (get_here_doc_input(limiter, pipe_fd))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		free(limiter);
		return (true);
	}
	close(pipe_fd[1]);
	free(limiter);
	return (add_new_fd(here_docs_fds, pipe_fd[0]));
}

static bool	get_here_doc_input(char *limiter, int pipe_fd[2])
{
	pid_t	pid;
	char	*input;

	pid = fork();
	if (pid == -1)
		return (true);
	if (pid == 0)
	{
		input = get_next_line(STDIN_FILENO);
		while (input != NULL && ft_strcmp(input, limiter) != 0)
		{
			ft_putstr_fd(input, pipe_fd[1]);
			free(input);
			input = get_next_line(STDIN_FILENO);
		}
		free(input);
		free(limiter);
		// TODO FREE ALL THE PROGRAM
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (false);
}

static bool	add_new_fd(t_list_i **here_docs_fds, int fd)
{
	t_list_i	*new_node;

	new_node = ft_lsti_new(fd);
	if (new_node == NULL)
	{
		close(fd);
		return (true);
	}
	ft_lsti_add_front(here_docs_fds, new_node);
	return (false);
}
