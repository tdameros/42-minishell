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

char	*get_input(void);
int		deal_input(char *input);

int	main(int argc, char **argv)
{
	t_list	*tokens;

	(void) argc;
	tokens = get_tokens(argv[1]);
	print_tokens(tokens);
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
