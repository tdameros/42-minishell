/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:21:59 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 01:48:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "interactive.h"
#include "minishell_signal.h"
#include "exit_code.h"
#include "expansions.h"

static int	loop_interactive_parsing(char **command, t_minishell *minishell);
static int	interactive_quotes_parsing(char **command, t_minishell *minishell);
static int	interactive_syntax_parsing(char **command, t_minishell *minishell);
static int	leave_run_interactive_parsing(t_minishell *minishell, int ret);

int	run_interactive_parsing(char **command, t_minishell *minishell)
{
	int		return_code;

	if (init_interactive_signal_handling() < 0)
		return (set_exit_code(-1));
	return_code = get_here_docs_if_valid_syntax(*command, *command, minishell);
	if (return_code != 0)
		return (leave_run_interactive_parsing(minishell, return_code));
	return_code = loop_interactive_parsing(command, minishell);
	if (return_code != 0)
		return (leave_run_interactive_parsing(minishell, return_code));
	minishell->tokens = get_tokens(*command);
	if (minishell->tokens == NULL)
		return (leave_run_interactive_parsing(minishell, 1));
	if (simplify_tokens(&minishell->tokens))
		return (leave_run_interactive_parsing(minishell, -1));
	if (replace_alias(minishell->tokens, minishell->alias) < 0)
		return (leave_run_interactive_parsing(minishell, -1));
	ft_lst_reverse(&minishell->here_docs);
	return (leave_run_interactive_parsing(minishell, 0));
}

static int	loop_interactive_parsing(char **command, t_minishell *minishell)
{
	int		return_code;

	return_code = interactive_quotes_parsing(command, minishell);
	if (return_code != -1)
		return (return_code);
	return_code = interactive_syntax_parsing(command, minishell);
	if (return_code != -1)
		return (return_code);
	return (0);
}

static int	interactive_quotes_parsing(char **command, t_minishell *minishell)
{
	int	return_code;

	if (!is_valid_quote(*command))
	{
		return_code = get_input_command(command, "\n", minishell);
		if (return_code != 0)
			return (return_code);
		return (loop_interactive_parsing(command, minishell));
	}
	return (-1);
}

static int	interactive_syntax_parsing(char **command, t_minishell *minishell)
{
	int		return_code;
	t_list	*tokens;

	tokens = get_tokens(*command);
	if (tokens == NULL)
		return (ft_lstclear(&tokens, &free_token), 1);
	return_code = parse_syntax(tokens);
	ft_lstclear(&tokens, &free_token);
	if (return_code < 0)
		return (2);
	if (return_code == 0)
	{
		return_code = get_input_command(command, " ", minishell);
		if (return_code != 0)
			return (return_code);
		return (loop_interactive_parsing(command, minishell));
	}
	return (-1);
}

static int	leave_run_interactive_parsing(t_minishell *minishell, int ret)
{
	if (ret != 0)
	{
		ft_lstclear(&minishell->tokens, &free_token);
		ft_lst_of_lst_clear(&minishell->here_docs, &free);
	}
	if (signal_init_handling_outside_execution() < 0)
		ret = set_exit_code(-1);
	return (ret);
}
