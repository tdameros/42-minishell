

#include "minishell_struct.h"
#include "lexer.h"
#include "error.h"
#include "parser.h"
#include "execution.h"

static int	handle_here_docs(t_minishell *minishell);

int	execute_single_line_command(t_minishell *minishell, char *command,
		char *line)
{
	if (is_valid_quote(command) == 0)
	{
		print_error(__FUNCTION__ , line,
			"no matching `\"' found\n");
		return (1);
	}
	minishell->tokens = get_tokens(command);
	minishell->here_docs = NULL;
	if (parse_syntax(minishell->tokens) < 1)
	{
		ft_lstclear(&minishell->tokens, &free_token);
		print_error(__FUNCTION__ , line, "handle error"); // TODO handle error
		return (2);
	}
	if (handle_here_docs(minishell) < 0)
		return (-1);
	if (simplify_tokens(&minishell->tokens))
	{
		ft_lstclear(&minishell->tokens, &free_token);
		ft_lstclear(&minishell->here_docs, NULL);
		print_error(NULL, "simplify_tokens() failed\n", get_error());
		return (-1);
	}
//	print_tokens(minishell->tokens);
	execute_commands(minishell);
	return (0);
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
				"here-document delimited by end-of-file\n");
			new_node = ft_lstnew(NULL);
			if (new_node == NULL)
			{
				ft_lstclear(&minishell->here_docs, NULL);
				ft_lstclear(&minishell->tokens, &free_token);
				print_error(__FUNCTION__ , "malloc failed", get_error());
				return (-1);
			}
			ft_lstadd_front(&minishell->here_docs, new_node);
		}
		tokens = tokens->next;
	}
	return (0);
}
