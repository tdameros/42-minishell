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

#include "parser.h"
#include "exit_code.h"

int	parse_tokens(t_list	**tokens)
{
	if (parse_syntax(*tokens) != 1)
	{
		exit_code(2);
		return (-1);
	}
	if (simplify_tokens(tokens))
		return (-1);
	return (0);
}
