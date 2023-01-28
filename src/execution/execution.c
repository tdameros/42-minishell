/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:24:00 by vfries            #+#    #+#             */
/*   Updated: 2023/01/28 10:10:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell_fork.h"
#include "env_variables.h"
#include <sys/wait.h>
#include <stdlib.h>

#define CTRL_C_EXIT_CODE 130

void	execute_commands(t_list **tokens, t_hashmap env_variables,
		t_list **here_docs)
{
	int	*exit_code;

	exit_code = ft_hm_get_content(env_variables, LAST_EXIT_CODE);
	execute_commands_loop(tokens, env_variables, here_docs,
		exit_code);
	ft_lstclear(tokens, &free_token);
	ft_lst_of_lst_clear(here_docs, &free);
	if (g_forks != (void *)-1)
		return ;
	*exit_code = CTRL_C_EXIT_CODE;
	g_forks = NULL;
	return (CTRL_C_EXIT_CODE);
}

int	execute_commands_loop(t_list *tokens, t_hashmap env_variables,
				t_list *here_docs, int *exit_code)
{
}
