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
static void	restore_signals(struct termios termios_save);

int	run_interactive_parsing(char **command, t_minishell *minishell)
{
	int		return_code;

	init_interactive_signal_handling_interactive(); // TODO secure me
	return_code = get_here_docs(*command, &minishell->here_docs);
	if (return_code != 0)
		return (restore_signals(minishell->termios_save), return_code);
	return_code = loop_interactive_parsing(command, &minishell->here_docs);
	if (return_code != 0)
		return (restore_signals(minishell->termios_save), return_code);
	minishell->tokens = get_tokens(*command);
	if (minishell->tokens == NULL)
		return (restore_signals(minishell->termios_save), 1);
	simplify_tokens(&minishell->tokens); // TODO check if simplify token failed (check return value)
	ft_lst_reverse(&minishell->here_docs);
	restore_signals(minishell->termios_save);
	return (0);
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

static void	restore_signals(struct termios termios_save)
{
	if (signal_init_handling_outside_execution() < 0)
		exit_code(-1);
	if (terminal_restore(termios_save) < 0)
		exit_code(-1);
	if (terminal_disable_ctrl_backslash_output() < 0)
		exit_code(-1);
}
