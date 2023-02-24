/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:09:43 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/24 10:09:45 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "get_here_docs.h"
#include "minishell_struct.h"

int	get_here_docs_if_valid_syntax(char *command, char *complete_command,
									t_minishell *minishell)
{
	t_list	*tokens;
	int		return_code;

	tokens = get_tokens(complete_command);
	if (tokens == NULL)
		return (1);
	ft_lstclear(&minishell->tokens, free_token);
	minishell->tokens = tokens;
	if (parse_syntax(tokens) < 0)
		return (ft_lstclear(&minishell->tokens, free_token), 2);
	ft_lstclear(&minishell->tokens, free_token);
	tokens = get_tokens(command);
	minishell->tokens = tokens;
	return_code = get_here_docs(tokens, minishell);
	ft_lstclear(&minishell->tokens, free_token);
	return (return_code);
}
