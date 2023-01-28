/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:01:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 14:44:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "error.h"

void	print_error(char *command, char *context, char *error)
{
	if (context != NULL)
		ft_printf("minishell: %s: %s: %s\n", command, context, error);
	else
		ft_printf("minishell: %s: %s\n", command, error);
}

char	*get_name(t_list *token)
{
	return (((t_token *)token->content)->args[0]);
}

char	*get_error(void)
{
	return (strerror(errno));
}
