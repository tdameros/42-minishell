/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 06:22:16 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_here_docs.h"
#include "lexer.h"
#include "env_variables.h"
#include "parser.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "lexer.h"
#include "quote.h"

#define PROMPT "➜ minishell-1.0$ "

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "➜ minishell-1.0$ "

int	execute_commands(t_list *tokens, t_list_i *here_docs);

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*save;
	t_list		*tokens;
	t_list_i	*here_docs;
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
		if (tokens == NULL)
			ft_printf("Malloc failed\n");
		remove_quotes(tokens);

		print_tokens(tokens);

		ft_printf("\n\n------------------------------------------------\n\n\n");

		if (simplify_tokens(&tokens, env_variables))
			ft_printf("simplified_tokens failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		print_tokens(tokens);


		here_docs = get_here_docs(tokens);
		while (here_docs != NULL)
		{
			char *gnl = get_next_line(here_docs->content);
			while (gnl != NULL)
			{
				ft_printf("%s", gnl);
				free(gnl);
				gnl = get_next_line(here_docs->content);
			}
			ft_printf("(null)\n");
			close(here_docs->content);
			ft_lsti_get_next_free_current(&here_docs);
		}
		execute_commands(tokens, here_docs);
		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&env_variables, &free);
	return (0);
}
