/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/27 07:27:44 by vfries           ###   ########lyon.fr   */
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
#include "execution.h"

#define PROMPT "➜ minishell-1.0$ "

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "➜ minishell-1.0$ "

static void	print_here_docs(t_list *here_docs);

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	char		*save;
	t_list		*tokens;
	t_list		*here_docs;
	t_hashmap	env_variables;

	(void)argc;
	(void)argv;

	env_variables = get_env_variables(envp);
	// print_env_variables(env_variables);

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

		// print_tokens(tokens);

		ft_printf("\n\n------------------------------------------------\n\n\n");

		if (simplify_tokens(&tokens, env_variables))
			ft_printf("simplified_tokens failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		// print_tokens(tokens);


		if (get_here_docs(&here_docs, tokens))
			ft_printf("get_here_docs() failed\n");
		print_here_docs(here_docs);

		// execute_commands(tokens, env_variables, -1, &here_docs);
		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&env_variables, &free);
	return (0);
}

static void	print_here_docs(t_list *here_docs)
{
	t_list	*cursor;
	int		i;

	i = 0;
	ft_printf("========= HERE DOCS ==========\n");
	while (here_docs != NULL)
	{
		ft_printf("========= HERE DOC %d ==========\n", i);
		ft_printf("         (Reversed)\n");
		cursor = here_docs->content;
		while (cursor != NULL)
		{
			ft_printf("%s", cursor->content);
			cursor = cursor->next;
		}
		here_docs = here_docs->next;
		i++;
	}
}
