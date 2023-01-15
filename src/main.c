/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/01/14 19:05:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>
#include <stdio.h>

char	*get_input(void);
void	deal_input(char *input);
int	is_operator(char *string);

int	main()
{
//	char	*input;
//
//	input = get_input();
//	while (input != NULL && ft_strcmp(input, "exit\n") != 0)
//	{
//		deal_input(input);
//		free(input);
//		input = get_input();
//	}
//	if (input != NULL)
//		free(input);
	ft_printf("%d\n", is_operator())
	return (0);
}
