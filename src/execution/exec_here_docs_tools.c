/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_docs_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:50:09 by vfries            #+#    #+#             */
/*   Updated: 2023/02/05 23:11:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include <stdlib.h>

void		skip_token_here_docs(t_list *tokens, t_list **here_docs);
static void	free_one_here_doc(t_list **here_docs);
int			read_here_doc(t_list **here_docs);

void	skip_tokens_here_docs(t_list *tokens, t_list **here_docs)
{
	while (tokens != NULL)
	{
		skip_token_here_docs(tokens, here_docs);
		tokens = tokens->next;
	}
}

void	skip_token_here_docs(t_list *tokens, t_list **here_docs)
{
	t_token	*token;
	t_list	*files;

	token = tokens->content;
	skip_tokens_here_docs(token->subshell, here_docs);
	files = token->files;
	while (files != NULL)
	{
		token = files->content;
		if (token->operator == HERE_DOC)
			free_one_here_doc(here_docs);
		files = files->next;
	}
}

static void	free_one_here_doc(t_list **here_docs)
{
	t_list	*here_doc;

	here_doc = (*here_docs)->content;
	ft_lstclear(&here_doc, &free);
	ft_lst_get_next_free_current(here_docs, NULL); // TODO check if this really should be NULL
}

int	read_here_doc(t_list **here_docs)
{
	t_list	*here_doc;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		free_one_here_doc(here_docs);
		return (-1);
	}
	here_doc = (*here_docs)->content;
	while (here_doc != NULL)
	{
		ft_putstr_fd(here_doc->content, pipe_fd[1]);
		here_doc = here_doc->next;
	}
	close(pipe_fd[1]);
	free_one_here_doc(here_docs);
	return (pipe_fd[0]);
}
