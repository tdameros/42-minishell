/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:40:50 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 21:48:05 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_struct.h"
#include "lexer.h"

void	exec_free_minishell(t_minishell *minishell)
{
	ft_hm_clear(&minishell->env_variables, &free);
	ft_lstclear(&minishell->tokens, &free_token);
	ft_lst_of_lst_clear(&minishell->here_docs, &free);
}
