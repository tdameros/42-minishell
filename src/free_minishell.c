/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:12:21 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/24 10:12:22 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_struct.h"
#include "lexer.h"

void	free_minishell(t_minishell *minishell)
{
	ft_hm_clear(&minishell->env_variables, &free);
	ft_hm_clear(&minishell->alias, &free);
	ft_lstclear(&minishell->tokens, &free_token);
	ft_lst_of_lst_clear(&minishell->here_docs, &free);
}
