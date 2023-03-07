/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:37:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/06 00:37:19 by vfries           ###   ########.fr       */
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
#include "prompt.h"

static char	*get_command(t_hashmap env_variables, bool colored_prompt);
static int	run_interactive_command(char **command, t_minishell *minishell);

int	run_interactive_shell(t_minishell *minishell, bool colored_prompt)
{
	char	*command;

	command = get_command(minishell->env_variables, colored_prompt);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		if (run_interactive_command(&command, minishell) < 0)
			break ;
		command = get_command(minishell->env_variables, colored_prompt);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&minishell->env_variables, &free);
	return (exit_code(GET));
}

static char	*get_command(t_hashmap env_variables, bool colored_prompt)
{
	char	*prompt;
	char	*command;

	if (isatty(STDIN_FILENO) == false)
		return (readline("minishell$ "));
	prompt = get_prompt(env_variables, colored_prompt);
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
