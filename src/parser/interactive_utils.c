/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 00:46:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/11 00:46:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "error.h"
#include "readline/readline.h"

static void	interactive_signal_handler(int sig);

void	init_interactive_signal_handling(void)
{
	struct sigaction	action;

	action.sa_handler = &interactive_signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

static void	interactive_signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}

int	set_end_of_file(char **command)
{

	free(*command);
	*command = NULL;
	print_error(NULL, "syntax error", "unexpected end of file");
	return (3);
}

char	*get_command_from_fd(int fd)
{
	char	*command;
	char	*new_command;
	char	*line;

	command = get_next_line(fd);
	if (command == NULL)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_command = ft_strjoin(command, line);
		free(command);
		free(line);
		if (new_command == NULL)
			return (NULL);
		command = new_command;
		line = get_next_line(fd);
	}
	return (command);
}
