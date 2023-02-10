/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:45:10 by vfries            #+#    #+#             */
/*   Updated: 2023/02/10 16:12:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "exit_code.h"


int	parse_tokens(t_list	**tokens, t_hashmap env_variables)
{
	if (parse_syntax(*tokens) != 1)
	{
		exit_code(2);
		return (-1);
	}
	if (simplify_tokens(tokens, env_variables))
		return (-1);
	return (0);
}

//static int check_syntax(t_list *tokens)
//{
//	char *new_command;
//	char *temp;
//
//	while (parse_syntax())
//	{
//		temp = readline("> ");
//		new_command = ft_strjoin_three(command, "\n",temp);
//		if (new_command == NULL)
//		{
//			free(command);
//			return (NULL);
//		}
//		free(command);
//		command = new_command;
//	}
//	return (command);
//}
