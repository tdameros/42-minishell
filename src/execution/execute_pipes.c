/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:44:03 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 16:42:10 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"
#include "env_variables.h"
#include "execution.h"
#include "minishell_signal.h"
#include "exit_code.h"
#include "expansions.h"
#include <sys/wait.h>
#include <stdlib.h>

static t_list	*create_sub_tokens(t_list **tokens);
static int		execute_pipes_sub_tokens(t_minishell *minishell,
					t_list **sub_tokens);

void	execute_pipes(t_minishell *minishell)
{
	t_list	*sub_tokens;
	int		io_save[2];

	sub_tokens = create_sub_tokens(&minishell->tokens);
	if (signal_init_handling_pipes() < 0)
	{
		exit_code(-1);
		return ;
	}
	if (save_io("Pipes", io_save) < 0)
	{
		exit_code(-1);
		return ;
	}
	exit_code(execute_pipes_sub_tokens(minishell, &sub_tokens));
	// skip_tokens_here_docs(sub_tokens, here_docs);
	if (restore_io_and_close_io_save(io_save, "Pipes") < 0)
		exit_code(-1);
	if (signal_init_handling_inside_execution() < 0)
		exit_code(-1);
	ft_lstclear(&sub_tokens, &free_token);
}

static t_list	*create_sub_tokens(t_list **tokens)
{
	t_list	*sub_tokens;
	t_token	*token;

	sub_tokens = NULL;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->type == OPERATOR && token->operator != PIPE)
			return (ft_lst_reverse(&sub_tokens));
		else if (token->operator == PIPE)
			ft_lst_get_next_free_current(tokens, &free_token);
		else
			ft_lst_push(&sub_tokens, tokens);
	}
	return (ft_lst_reverse(&sub_tokens));
}

// Do not secure close(STDIN_FILENO) in this function. It is normal if it
// fails in some cases
static int	execute_pipes_sub_tokens(t_minishell *minishell,
				t_list **sub_tokens)
{
	int		ret;
	pid_t	pid;

	if (sub_tokens == NULL || *sub_tokens == NULL)
		return (-1);
	if ((*sub_tokens)->next == NULL)
	{
		execute_command_no_pipe(minishell, sub_tokens, true);
		return (exit_code(GET));
	}
	pid = execute_piped_command(minishell, sub_tokens);
	if (pid == -1)
		return (-1);
	ret = execute_pipes_sub_tokens(minishell, sub_tokens);
	close(STDIN_FILENO);
	if (pid != -1)
		waitpid(pid, NULL, 0);
	return (ret);
}
