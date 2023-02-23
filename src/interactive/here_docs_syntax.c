#include <stdlib.h>

#include "libft.h"

#include "lexer.h"
#include "parser.h"
#include "get_here_docs.h"
#include "minishell_struct.h"

int	get_here_docs_if_valid_syntax(char *command, t_minishell *minishell)
{
	t_list	*tokens;
	int		return_code;

	tokens = get_tokens(command);
	if (tokens == NULL)
		return (1);
	ft_lstclear(&minishell->tokens, free_token);
	minishell->tokens = tokens;
	if (parse_syntax(tokens) < 0)
		return (ft_lstclear(&minishell->tokens, free_token), 2);
	return_code = get_here_docs(tokens, minishell);
	ft_lstclear(&minishell->tokens, free_token);
	return (return_code);
}
