/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_line_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:51:22 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/09 01:54:46 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parser.h"
#include "execution.h"
#include "exit_code.h"

static int	bad_quote(char *line);
static int	handle_here_docs(t_minishell *minishell);

int	execute_single_line_command(t_minishell *minishell, char *line)
{
	if (line == NULL || *line == '\0')
		return (exit_code(GET));
	if (is_valid_quote(line) == 0)
		return (bad_quote(line));
	minishell->tokens = get_tokens(line);
	if (minishell->tokens == NULL)
		return (exit_code(GET));
	minishell->here_docs = NULL;
	if (parse_syntax(minishell->tokens) < 1)
	{
		ft_lstclear(&minishell->tokens, &free_token);
		print_error("execute_single_comamnd_command()", "syntax error", line);
		return (2);
	}
	if (handle_here_docs(minishell) < 0)
		return (-1);
	if (simplify_tokens(&minishell->tokens))
	{
		ft_lstclear(&minishell->tokens, &free_token);
		ft_lstclear(&minishell->here_docs, NULL);
		print_error(NULL, "simplify_tokens() failed", get_error());
		return (-1);
	}
	execute_commands(minishell);
	return (exit_code(GET));
}

static int	bad_quote(char *line)
{
	print_error("execute_single_line_command()", line,
		"no matching `\"' found\n");
	return (1);
}

static int	handle_here_docs(t_minishell *minishell)
{
	t_list	*new_node;
	t_list	*tokens;
	t_token	*token;

	tokens = minishell->tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == OPERATOR && token->operator == HERE_DOC)
		{
			print_error(NULL, "warning",
				"here-document delimited by end-of-file");
			new_node = ft_lstnew(NULL);
			if (new_node == NULL)
			{
				ft_lstclear(&minishell->here_docs, NULL);
				ft_lstclear(&minishell->tokens, &free_token);
				print_error("handle_here_docs()", "malloc failed", get_error());
				return (-1);
			}
			ft_lstadd_front(&minishell->here_docs, new_node);
		}
		tokens = tokens->next;
	}
	return (0);
}
