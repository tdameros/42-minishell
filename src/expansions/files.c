/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:02:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/10 00:02:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <error.h>
#include "lexer.h"
#include "expansions.h"

static int	file_expansion(t_token *file, t_hashmap env_variables);
static int	set_ambiguous_file(t_token *file);
static int	wildcards_file_expansion(t_token *file);

int	apply_files_expansion(t_list *files, t_hashmap env_variables)
{
	while (files != NULL)
	{
		if (file_expansion(files->content, env_variables) < 0)
			return (-1);
		files = files->next;
	}
	return (0);
}

static int	file_expansion(t_token *file, t_hashmap env_variables)
{
	char	*new_name;
	int		return_code;

	new_name = strdup_with_parameters_quote(file->name, env_variables);
	if (new_name == NULL)
		return (-1);
	free(file->name);
	file->name = new_name;
	if (ft_count_args_after_split_unless_quotes(file->name) > 1
		|| ft_strlen(file->name) == 0)
		return (set_ambiguous_file(file));
	return_code = wildcards_file_expansion(file);
	if (return_code < 0)
		return (-1);
	else if (return_code == 0)
		return (0);
	new_name = strdup_without_quote(file->name);
	if (file->name == NULL)
		return (-1);
	free(file->name);
	file->name = new_name;
	return (0);
}

static int	set_ambiguous_file(t_token *file)
{
	free(file->name);
	file->name = NULL;
	return (0);
}

static int	wildcards_file_expansion(t_token *file)
{
	t_list	*wildcards;

	wildcards = get_wildcards_list(file->name);
	if (errno != 0)
		return (-1);
	if (ft_lstsize(wildcards) > 1)
	{
		ft_lstclear(&wildcards, free);
		set_ambiguous_file(file);
		return (0);
	}
	if (ft_lstsize(wildcards) == 1)
	{
		free(file->name);
		file->name = wildcards->content;
		ft_lstclear(&wildcards, NULL);
	}
	return (1);
}
