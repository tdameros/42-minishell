/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 09:07:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env_variables.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "➜ minishell-1.0$ "

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*save;
	t_list		*tokens;
	t_hashmap	env_variables;

	(void)argc;
	(void)argv;

	env_variables = get_env_variables(envp);
	print_env_variables(env_variables);

	command = readline(PROMPT);
	while (command != NULL && ft_strcmp(command, "exit")) // TODO should be able to do "echo test && exit"
	{
		save = command;
		while (!is_valid_quote(save))
		{
			command = readline("> ");
			save = ft_strjoin(save, command);
		}
		add_history(save);

		tokens = get_tokens(save);
		remove_quotes(tokens);

		print_tokens(tokens);

		ft_printf("\n\n------------------------------------------------\n\n\n");

		simplify_tokens(&tokens, env_variables);
		print_tokens(tokens);

		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&env_variables, &free);
	return (0);
}
