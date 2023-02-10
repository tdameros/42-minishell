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
#include <errno.h>
#include "expansions.h"
#include "lexer.h"

static int	apply_arguments_expansion(t_token *token, t_hashmap env_variables);

int	apply_token_expansion(t_token *token, t_hashmap env_variables)
{
	if (apply_arguments_expansion(token, env_variables) < 0)
		return (-1);
	if (apply_files_expansion(token->files, env_variables) < 0)
		return (-1);
	return (0);
}

static int	apply_arguments_expansion(t_token *token, t_hashmap env_variables)
{
	char	**temp;

	if (insert_parameters_in_args(token->args, env_variables) < 0)
		return (-1);
	temp = split_args(token->args);
	if (temp == NULL)
		return (-1);
	ft_free_split(token->args);
	token->args = temp;
	temp = duplicate_args_with_wildcards(token->args);
	if (temp == NULL)
		return (-1);
	ft_free_split(token->args);
	token->args = temp;
	if (remove_quotes_in_args(token->args) < 0)
		return (-1);
	return (0);
}
