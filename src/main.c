/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 21:58:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_here_docs.h"
#include "lexer.h"
#include "env_variables.h"
#include "parser.h"
#include "libft.h"
#include "execution.h"
#include "built_in.h"
#include "exit_code.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "quote.h"
#include "minishell_signal.h"

#define PROMPT "➜ minishell-1.0$ "
#include "error.h"
void	print_here_docs(t_list *here_docs);
void	test_get_envp(t_hashmap env_variables);

#include "expansions.h"
void	dummy(void *content)
{
	ft_printf("%s\n", content);
}

void	pass(void)
{
}
int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_list		*tokens;
	t_list		*here_docs;
	t_hashmap	env_variables;

	(void)argc;
	(void)argv;
	init_main_signal_handling();
	env_variables = get_env_variables(envp);
	// test_get_envp(env_variables);
	if (init_exit_code(env_variables))
		ft_printf("Error handling\n"); // TODO
	command = readline(PROMPT);
	while (command != NULL && ft_strcmp(command, "exit"))
	{
		if (run_interactive_parsing(&command, &tokens) > 0)
		{
			simplify_tokens(&tokens, env_variables);
//			print_tokens(tokens);
			if (get_here_docs(&here_docs, tokens))
				ft_printf("get_here_docs() failed\n");
			execute_commands(&tokens, env_variables, &here_docs);
		}
		else
			exit_code(2);
		if (command == NULL)
		{
			ft_hm_clear(&env_variables, &free);
			ft_putstr("exit\n");
			exit(2);
		}
		add_history(command);
		free(command);
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

	envp = get_all_envp(env_variables);
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
