//
// Created by tdameros on 2/11/23.
//
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "interactive.h"
#include "minishell_signal.h"
#include "exit_code.h"
#include "get_here_docs.h"
#include "terminal.h"

static int	loop_interactive_parsing(char **command, t_list **here_docs);
static int	interactive_quotes_parsing(char **command, t_list **here_docs);
static int	interactive_syntax_parsing(char **command, t_list **here_docs);
static int	leave_run_interactive_parsing(t_minishell *minishell, int ret);

int	run_interactive_parsing(char **command, t_minishell *minishell)
{
	int		return_code;

	if (init_interactive_signal_handling() < 0)
		return (exit_code(-1));
	return_code = get_here_docs(*command, &minishell->here_docs);
	if (return_code != 0)
		return (leave_run_interactive_parsing(minishell, return_code));
	return_code = loop_interactive_parsing(command, &minishell->here_docs);
	if (return_code != 0)
		return (leave_run_interactive_parsing(minishell, return_code));
	minishell->tokens = get_tokens(*command);
	if (minishell->tokens == NULL)
		return (leave_run_interactive_parsing(minishell, 1));
	if (simplify_tokens(&minishell->tokens))
		return (leave_run_interactive_parsing(minishell, -1));
	ft_lst_reverse(&minishell->here_docs);
	return (leave_run_interactive_parsing(minishell, 0));
}

static int	loop_interactive_parsing(char **command, t_list **here_docs)
{
	int		return_code;

	return_code = interactive_quotes_parsing(command, here_docs);
	if (return_code != -1)
		return (return_code);
	return_code = interactive_syntax_parsing(command, here_docs);
	if (return_code != -1)
		return (return_code);
	return (0);
}

static int	interactive_quotes_parsing(char **command, t_list **here_docs)
{
	int	return_code;

	if (!is_valid_quote(*command))
	{
		return_code = get_input_command(command, "\n", here_docs);
		if (return_code != 0)
			return (return_code);
		return (loop_interactive_parsing(command, here_docs));
	}
	return (-1);
}

static int	interactive_syntax_parsing(char **command, t_list **here_docs)
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
	else if (return_code == 0)
	{
		return_code = get_input_command(command, " ", here_docs);
		if (return_code == 2)
		{
			free(*command);
			*command = NULL;
		}
		if (return_code != 0)
			return (return_code);
		return (loop_interactive_parsing(command, here_docs));
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
		ret = exit_code(-1);
	return (ret);
}
