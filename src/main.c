/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/30 06:39:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_here_docs.h"
#include "lexer.h"
#include "env_variables.h"
#include "parser.h"
#include "libft.h"
#include "execution.h"
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

void	print_here_docs(t_list *here_docs);
void	test_get_envp(t_hashmap env_variables);

static int	add_last_exit_code(t_hashmap env_variables);

void	dummy(void)
{
	return ;
}

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
	if (add_last_exit_code(env_variables))
	{
		ft_hm_clear(&env_variables, &free);
		return (-1);
	}
	// test_get_envp(env_variables);

	command = readline(PROMPT);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		save = command;
		while (!is_valid_quote(save))
		{
			command = readline("> ");
			save = ft_strjoin(save, command);
		}
		add_history(save);

		tokens = get_tokens(save);
		// if (tokens == NULL)
		// 	ft_printf("Malloc failed\n");
		remove_quotes(tokens);

		// print_tokens(tokens);

//		ft_printf("\n\n------------------------------------------------\n\n\n");

		if (simplify_tokens(&tokens, env_variables))
			ft_printf("simplified_tokens failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		// print_tokens(tokens);


		if (get_here_docs(&here_docs, tokens))
			ft_printf("get_here_docs() failed\n");
		// ft_printf("%p\n", here_docs->content);
		// print_here_docs(here_docs);

		dummy();
		execute_commands(&tokens, env_variables, &here_docs);
		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	ft_hm_clear(&env_variables, &free);
	return (0);
}

void	print_here_docs(t_list *here_docs)
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
		// ft_printf("%c", ((char *)cursor->content)[0]);
		while (cursor != NULL)
		{
			ft_printf("%s", cursor->content);
			cursor = cursor->next;
		}
		here_docs = here_docs->next;
		i++;
	}
}

void	test_get_envp(t_hashmap env_variables)
{
	char	**envp;
	int		i;

	envp = get_envp(env_variables);
	if (envp == NULL)
	{
		ft_printf("ENVP == NULL\n");
		return ;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	ft_printf("(null)\n");
	ft_free_split(envp);
}

static int	add_last_exit_code(t_hashmap env_variables)
{
	int	*exit_code;

	exit_code = malloc(sizeof(int));
	if (exit_code == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, LAST_EXIT_CODE, exit_code, &free))
	{
		free(exit_code);
		return (-1);
	}
	*exit_code = 0;
	return (0);
}
