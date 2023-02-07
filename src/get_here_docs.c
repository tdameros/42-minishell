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
#include <stdlib.h>

#define HERE_DOC_PROMPT "> "

static int	add_here_docs(t_list **here_docs, t_list *files);
static int	add_here_doc(t_list **here_docs, char *limiter);
static int	get_input(t_list **input_lst, char *limiter);
static int	add_input(t_list **input_lst, int *pipe_fd);

int	get_here_docs(t_list **here_docs, t_list *tokens)
{
	t_token	*token;

	*here_docs = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type != OPERATOR && add_here_docs(here_docs, token->files))
		{
			ft_lst_of_lst_clear(here_docs, &free);
			return (-1);
		}
		tokens = tokens->next;
	}
	ft_lst_reverse(here_docs);
	return (0);
}

static int	add_here_docs(t_list **here_docs, t_list *files)
{
	t_token	*token;

	while (files != NULL)
	{
		token = files->content;
		if (token->operator == HERE_DOC && add_here_doc(here_docs, token->name))
			return (-1);
		files = files->next;
	}
	return (0);
}

static int	add_here_doc(t_list **here_docs, char *limiter)
{
	t_list	*input;
	t_list	*new_node;

	limiter = ft_strjoin(limiter, "\n");
	if (limiter == NULL)
		return (-1);
	input = NULL;
	if (get_input(&input, limiter) == -1)
	{
		free(limiter);
		ft_lstclear(&input, &free);
		return (-1);
	}
	new_node = ft_lstnew(input);
	if (new_node == NULL)
	{
		free(limiter);
		ft_lstclear(&input, &free);
		return (-1);
	}
	ft_lstadd_front(here_docs, new_node);
	free(limiter);
	return (0);
}

static int	get_input(t_list **input_lst, char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*input;

	// TODO Make this work with ctrl c handling
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid != 0)
		return (add_input(input_lst, pipe_fd));
	ft_putstr(HERE_DOC_PROMPT);
	input = get_next_line(STDIN_FILENO);
	while (input != NULL && ft_strcmp(input, limiter) != 0)
	{
		ft_putstr_fd(input, pipe_fd[1]);
		free(input);
		ft_putstr(HERE_DOC_PROMPT);
		input = get_next_line(STDIN_FILENO);
	}
	free(input);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(0);
}

static int	add_input(t_list **input_lst, int *pipe_fd)
{
	char	*input;
	t_list	*new_node;

	close(pipe_fd[1]);
	input = get_next_line(pipe_fd[0]);
	while (input != NULL)
	{
		new_node = ft_lstnew(input);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_front(input_lst, new_node);
		input = get_next_line(pipe_fd[0]);
	}
	close(pipe_fd[0]);
	return (0);
}
