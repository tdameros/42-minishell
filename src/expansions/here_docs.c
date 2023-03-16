/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:10:20 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 02:05:18 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "expansions.h"

static int	replace_parameter(t_list *here_doc, t_hashmap env_variables);
static int	count_here_docs_in_token(t_token *token);

int	apply_here_docs_expansions(t_token *token,
	t_list *here_docs, t_hashmap env_variables)
{
	int	count;
	int	index;

	count = count_here_docs_in_token(token);
	index = 0;
	while (index < count)
	{
		if (replace_parameter(here_docs->content, env_variables) < 0)
			return (-1);
		here_docs = here_docs->next;
		index++;
	}
	return (0);
}

static int	replace_parameter(t_list *here_doc, t_hashmap env_variables)
{
	char	*new_content;

	while (here_doc != NULL && here_doc->content != NULL)
	{
		new_content = strdup_with_parameters(here_doc->content, env_variables);
		if (new_content == NULL)
			return (-1);
		free(here_doc->content);
		here_doc->content = new_content;
		here_doc = here_doc->next;
	}
	return (0);
}

static int	count_here_docs_in_token(t_token *token)
{
	t_list	*files;
	t_token	*file;
	int		count;

	files = token->files;
	count = 0;
	while (files != NULL)
	{
		file = files->content;
		if (file->operator == HERE_DOC)
			count++;
		files = files->next;
	}
	return (count);
}
