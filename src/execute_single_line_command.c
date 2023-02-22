

#include "minishell_struct.h"
#include "lexer.h"
#include "quote.h"

int	execute_single_line_command(t_minishell *minishell, char *command)
{
	if (is_valid_quote(command) == 0)

	minishell->tokens = get_tokens(command);
}