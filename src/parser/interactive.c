/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 01:27:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/11 23:37:59 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h> /*	included to avoid compilation errors on mac OS with
						readline headers									*/
#include "readline/readline.h"
#include "parser.h"
#include "error.h"
#include "minishell_signal.h"

static int	run_forked_interactive_parsing(char **command, t_list **parsed_tokens);
static int	run_interactive_quotes_parsing(char **command);
static int	run_interactive_syntax_parsing(char **command,
				t_list **parsed_tokens);


#include <stdio.h>
int	run_interactive_parsing(char **command, t_list **parsed_tokens)
{
	// TODO : SECURE THE FONCTION (tomorrow)
	int	fd[2];
	int	pid;
	int	exit_code;

	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		// CLOSE FD
		return (1);
	else if (pid == 0)
	{
		init_interactive_signal_handling(); // SECURE SIGACTION
		close(fd[0]);
		exit_code = run_forked_interactive_parsing(command, parsed_tokens);
		dup2(fd[1], STDOUT_FILENO);
		if (exit_code == 0)
			ft_printf("%s", *command);
		close(fd[1]);
		ft_lstclear(parsed_tokens, free);
		exit(exit_code);
	}
	waitpid(pid, &exit_code, 0);
	exit_code = WEXITSTATUS(exit_code);
	close(fd[1]);
	if (exit_code == 0)
	{
		free(*command);
		*command = get_command_from_fd(fd[0]);
		*parsed_tokens = get_tokens(*command);
	}
	close(fd[0]);
	return (exit_code);
}

static int	run_forked_interactive_parsing(char **command, t_list **parsed_tokens)
{
	int		return_code;

	return_code = run_interactive_quotes_parsing(command);
	if (return_code != 0)
		return (return_code);
	return_code = run_interactive_syntax_parsing(command, parsed_tokens);
	ft_lstclear(parsed_tokens, &free_token);
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
			return (1);
		*command = new_command;
	}
	return (0);
}

static int	run_interactive_syntax_parsing(char **command,
											t_list **parsed_tokens)
{
	int		return_code;
	char	*line;
	char	*new_command;

	*parsed_tokens = get_tokens(*command);
	if (*parsed_tokens == NULL)
		return (1);
	return_code = parse_syntax(*parsed_tokens);
	if (return_code < 0)
		return (2);
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
			return (1);
		*command = new_command;
		return (run_interactive_parsing(command, parsed_tokens));
	}
	return (0);
}

