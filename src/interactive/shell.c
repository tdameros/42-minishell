/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:37:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/12 16:37:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "env_variables.h"
#include "interactive.h"
#include "readline/readline.h"
#include "readline/history.h"
#include "lexer.h"
#include "execution.h"
#include "exit_code.h"
#include "libft.h"

#define PROMPT "\e[32m➜ \e[36mminishell-1.0$ \x1b[0m"

int	run_interactive_shell(t_hashmap env_variables)
{
	char	*command;
	t_list	*here_docs;
	t_list	*tokens;
	int		return_code;

	(void ) env_variables;
	here_docs = NULL;
	tokens = NULL;
	command = readline(PROMPT);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		if (ft_strlen(command) > 0)
		{
			return_code = run_new_interactive_parsing(&command, &tokens, &here_docs);
			if (return_code != 0)
				exit_code(return_code);
			else
				execute_commands(&tokens, env_variables, &here_docs);
//			ft_printf("PARSING CODE : %d\n", return_code);
//			ft_printf("COMMAND : %s\n", command);
			add_history(command);
		}
		free(command);
		ft_lst_of_lst_clear(&here_docs, free);
		ft_lstclear(&tokens, &free_token);
		if (command == NULL)
			break ;
		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&env_variables, &free);
	return (0);
}
