/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/15 15:02:24 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "lexer.h"
#include "quote.h"

#define PROMPT "➜ minishell-1.0$ "

char	*get_input(void);
int		deal_input(char *input);

void	print_parsing_error(enum e_operators operator)
{
	char	*error;

	if (operator == OPEN_PARENTHESES)
		error = "(";
	else if (operator == CLOSE_PARENTHESES)
		error = ")";
	else if (operator == OR)
		error = "||";
	else if (operator == AND)
		error = "&&";
	else if (operator == PIPE)
		error = "|";
	else if (operator == INPUT_REDIRECT)
		error = "<";
	else if (operator == OUTPUT_REDIRECT)
		error = ">";
	else if (operator == HERE_DOC)
		error = "<<";
	else if (operator == APPEND)
		error = ">>";
	else
		error = "";
	ft_printf("minishell: syntax error near unexpected token `%s'\n", error);
}


int	main(void)
{
	char	*command;
	char	*save;
	enum e_operators	error;
	t_list	*tokens;

	command = readline(PROMPT);
	while (ft_strncmp(command, "exit", 4))
	{
		save = command;
		while (!is_valid_quote(save))
		{
			command = readline("> ");
			save = ft_strjoin(save, command);
		}
		add_history(save);
		save = ft_strtrim(save, " ");
		tokens = get_tokens(save);
		remove_quotes(tokens);
		print_tokens(tokens);
		if (!is_valid_operators(tokens, &error))
			print_parsing_error(error);
		else
			ft_printf("OK\n");
		command = readline(PROMPT);
	}
	return (0);
}
