/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:37:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/14 22:55:16 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell_struct.h"
#include "env_variables.h"
#include "interactive.h"
#include "execution.h"
#include "exit_code.h"
#include "libft.h"
#include "error.h"

#define ARROW "\001\e[32m\002\001➜\002"
#define PROMPT "\001\e[36m\002minishell-1.0$ \001\x1b[0m\002"

static int	run_interactive_command(char **command, t_minishell *minishell);

int	run_interactive_shell(t_minishell *minishell)
{
	char	*command;

	command = readline(ARROW" "PROMPT);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		if (run_interactive_command(&command, minishell) < 0)
			break ;
		command = readline(ARROW" "PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&minishell->env_variables, &free);
	return (exit_code(GET));
}

static int	run_interactive_command(char **command, t_minishell *minishell)
{
	int	return_code;

	errno = 0;
	if (ft_strlen(*command) > 0)
	{
		return_code = run_interactive_parsing(command, minishell);
		if (return_code != 0)
			exit_code(return_code);
		else
			execute_commands(minishell);
		add_history(*command);
	}
	free(*command);
	if (exit_code(GET) < 0)
	{
		print_error(NULL, "Fatal error with errno", get_error());
		ft_hm_clear(&minishell->env_variables, &free);
		return (-1);
	}
	if (*command == NULL)
		return (-1);
	return (0);
}
