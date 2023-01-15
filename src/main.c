/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/15 20:40:06 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_string.h"
#include <stdlib.h>
#include <stdio.h>
#include "ft_linked_list.h"
#include "tokens.h"

void	parse_tokens(t_list **tokens);

t_token	*new_token(enum e_type type, enum e_operators operator, char *name)
{
	t_token	*new_token = malloc(sizeof(t_token));

	new_token->type = type;
	new_token->operator = operator;
	new_token->name = name;

	return new_token;
}

void	print_list(t_list *tokens)
{
	while (tokens)
	{
		ft_printf("Type = %d\n", ((t_token *)tokens->content)->type);
		ft_printf("Operator = %d\n", ((t_token *)tokens->content)->operator);
		ft_printf("Name = %s\n", ((t_token *)tokens->content)->name);
		ft_printf("----------------------------------->\n");
		tokens = tokens->next;
	}
	ft_printf("(NULL)\n");
}

int	main(int argc, char **argv)
{
	t_list	*tokens;

	if (argc == 1)
	{
		ft_printf("No args!!!");
		return (1);
	}
	(void)argc;
	tokens = get_tokens(argv[1]);
	print_list(tokens);

	ft_printf("\n\n");

	parse_tokens(&tokens);
	print_list(tokens);
}
