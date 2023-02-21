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
#include "lexer.h"
#include "execution.h"
#include "exit_code.h"
#include "libft.h"
#include "error.h"

#define PROMPT "\e[32m➜ \e[36mminishell-1.0$ \x1b[0m"

int	run_interactive_shell(t_minishell *minishell)
{
	char	*command;
	int		return_code;

	command = readline(PROMPT);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		errno = 0;
		if (ft_strlen(command) > 0)
		{
			return_code = run_new_interactive_parsing(&command,
					&minishell->tokens, &minishell->here_docs);
			if (return_code != 0)
				exit_code(return_code);
			else
				execute_commands(minishell);
//			ft_printf("PARSING CODE : %d\n", return_code);
//			ft_printf("COMMAND : %s\n", command);
			add_history(command);
		}
		free(command);
		if (exit_code(GET) < 0)
		{
			print_error(NULL, "Fatal error with errno", get_error());
			ft_hm_clear(&minishell->env_variables, &free);
			return (1);
		}
		if (command == NULL)
			break ;
		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&minishell->env_variables, &free);
	return (0);
}
