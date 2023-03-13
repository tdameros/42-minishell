/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:37:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/09 17:18:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "interactive.h"
#include "execution.h"
#include "exit_code.h"
#include "error.h"
#include "prompt.h"

static char	*get_command(t_hashmap env_variables);
static int	run_interactive_command(char **command, t_minishell *minishell);

int	run_interactive_shell(t_minishell *minishell)
{
	char	*command;
	int		return_code;

	command = get_command(minishell->env_variables);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		return_code = run_interactive_command(&command, minishell);
		if (return_code < 0)
			break ;
		command = get_command(minishell->env_variables);
	}
	if (return_code >= 0)
	{
		free(command);
		ft_putstr("exit\n");
	}
	return (get_exit_code());
}

static char	*get_command(t_hashmap env_variables)
{
	char	*prompt;
	char	*command;

	if (isatty(STDIN_FILENO) == false)
		return (readline("minishell$ "));
	prompt = get_prompt(env_variables);
	if (prompt == NULL)
	{
		print_error(NULL, "failed to get prompt", get_error());
		return (NULL);
	}
	command = readline(prompt);
	free(prompt);
	return (command);
}

static int	run_interactive_command(char **command, t_minishell *minishell)
{
	int	return_code;

	errno = 0;
	if (ft_strlen(*command) > 0 && *ft_skip_set(*command, IFS) != '\0')
	{
		return_code = run_interactive_parsing(command, minishell);
		if (return_code != 0)
			set_exit_code(return_code);
		else
			execute_commands(minishell);
		add_history(*command);
	}
	free(*command);
	if (get_exit_code() < 0)
	{
		print_error(NULL, "Fatal error with errno", get_error());
		return (-1);
	}
	if (*command == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}
