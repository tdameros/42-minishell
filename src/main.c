/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 00:35:37 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "libft.h"
#include "quote.h"

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "➜ minishell-1.0$ "

int	main(int argc, char **argv)
{
	char	*command;
	char	*save;
	t_list	*tokens;

	(void)argc;
	(void)argv;
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

		simplify_tokens(&tokens);
		print_tokens(tokens);

		command = readline(PROMPT);
	}
	free(command);
	ft_putstr("exit\n");
	return (0);
}
