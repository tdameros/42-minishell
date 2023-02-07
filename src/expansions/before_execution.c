/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:54:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/05 01:54:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expansions.h"
#include "lexer.h"

static int	arguments_expansion(t_token *token, t_hashmap env_variables);
static int	files_expansion(t_list *files, t_hashmap env_variables);
static int	file_expansion(t_token *file, t_hashmap env_variables);

int	apply_expansions_before_exec(t_token *token, t_hashmap env_variables)
{
	if (arguments_expansion(token, env_variables) < 0)
		return (-1);
	if (files_expansion(token->files, env_variables) < 0)
		return (-1);
	return (0);
}

static int	arguments_expansion(t_token *token, t_hashmap env_variables)
{
	char	**temp;

	if (insert_parameters_in_args(token->args, env_variables) < 0)
		return (-1);
	temp = split_args(token->args);
	if (temp == NULL)
		return (-1);
	ft_free_split(token->args);
	token->args = temp;
	temp = duplicate_argument_with_wildcards(token->args);
	if (temp == NULL)
		return (-1);
	ft_free_split(token->args);
	token->args = temp;
	if (remove_quotes_in_args(token->args) < 0)
		return (-1);
	return (0);
}

static int	files_expansion(t_list *files, t_hashmap env_variables)
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

	new_name = strdup_with_parameters_quote(file->name, env_variables);
	if (new_name == NULL)
		return (-1);
	free(file->name);
	file->name = new_name;
	if (ft_count_args_after_split_unless_quotes(file->name) > 1
		|| ft_strlen(file->name) == 0)
	{
		free(file->name);
		file->name = NULL;
		return (0);
	}
	new_name = strdup_without_quote(new_name);
	if (file->name == NULL)
		return (-1);
	free(file->name);
	file->name = new_name;
	return (0);
}
