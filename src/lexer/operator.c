/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/15 14:06:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "tokens.h"

int	get_operator(char *string)
{
	if (ft_strncmp(string, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(string, ">>", 2) == 0)
		return (APPEND);
	else if (ft_strncmp(string, "&&", 2) == 0)
		return (AND);
	else if (ft_strncmp(string, "||", 2) == 0)
		return (OR);
	else if (ft_strncmp(string, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(string, ">", 1) == 0)
		return (OUTPUT_REDIRECT);
	else if (ft_strncmp(string, "<", 1) == 0)
		return (INPUT_REDIRECT);
	else if (ft_strncmp(string, "(", 1) == 0)
		return (OPEN_PARENTHESE);
	else if (ft_strncmp(string, ")", 1) == 0)
		return (CLOSE_PARENTHESE);
	return (-1);
}

int	add_operator_token(t_list **tokens, enum e_operators)
{
	t_token	*token;


}