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
#include "tokens.h"
#include "libft.h"

#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell-1.0$ "

char	*get_input(void);
int		deal_input(char *input);


int	main(void)
{
	char	*command;
	t_list	*tokens;

	command = readline(PROMPT);
	while (ft_strncmp(command, "exit", 4))
	{
		add_history(command);
		tokens = get_tokens(command);
		print_tokens(tokens);
		command = readline(PROMPT);
	}
//	char	*input;
//
//	input = get_input();
//	while (input != NULL && ft_strcmp(input, "exit\n") != 0)
//	{
//		if (deal_input(input) == -1)
//		{
//			free(input);
//			return (1);
//		}
//		free(input);
//		input = get_input();
//	}
//	if (input != NULL)
//		free(input);
//	else
//		ft_putstr("exit\n");
	return (0);
}
