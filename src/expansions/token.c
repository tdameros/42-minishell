/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:54:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/09 02:06:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int	apply_token_expansion(t_token *token, t_list *here_docs,
		t_hashmap env_variables)
{
	if (token->type != SUBSHELL
		&& apply_arguments_expansion(token, env_variables) < 0)
		return (-1);
	if (token->type != SUBSHELL && add_path(token, env_variables) < 0)
		return (-1);
	if (apply_files_expansion(token->files, env_variables) < 0)
		return (-1);
	if (apply_here_docs_expansions(token, here_docs, env_variables) < 0)
		return (-1);
	return (0);
}
