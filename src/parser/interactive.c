/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:27:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/10 01:27:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "parser.h"
#include "lexer.h"
#include "error.h"

static int	run_interactive_quotes_parsing(char **command);
static int	run_interactive_syntax_parsing(char **command, t_list **parsed_tokens);
static int	set_end_of_file(char **command);

int	run_interactive_parsing(char **command, t_list **parsed_tokens)
{
	int		return_code;

	return_code = run_interactive_quotes_parsing(command);
	if (return_code <= 0)
		return (return_code);
	return_code = run_interactive_syntax_parsing(command, parsed_tokens);
	return (return_code);
}

static int	run_interactive_quotes_parsing(char **command)
{
	char	*new_command;
	char	*line;

	while (!is_valid_quote(*command))
	{
		line = readline("> ");
		if (line == NULL)
			return (set_end_of_file(command));
		new_command = ft_strjoin_three(*command, "\n", line);
		free(*command);
		free(line);
		if (new_command == NULL)
			return (-1);
		*command = new_command;
	}
	return (1);
}

static int	run_interactive_syntax_parsing(char **command,
											t_list **parsed_tokens)
{
	int		return_code;
	char	*line;
	char	*new_command;

	*parsed_tokens = get_tokens(*command);
	if (*parsed_tokens == NULL)
		return (-1);
	return_code = parse_syntax(*parsed_tokens);
	if (return_code < 0)
		return (0);
	else if (return_code == 0)
	{
		ft_lstclear(parsed_tokens, &free_token);
		line = readline("> ");
		if (line == NULL)
			return (set_end_of_file(command));
		new_command = ft_strjoin_three(*command, " ", line);
		free(*command);
		free(line);
		if (new_command == NULL)
			return (-1);
		*command = new_command;
		return (run_interactive_parsing(command, parsed_tokens));
	}
	return (1);
}

static int	set_end_of_file(char **command)
{

	free(*command);
	*command = NULL;
	print_error(NULL, "syntax error", "unexpected end of file");
	return (0);
}