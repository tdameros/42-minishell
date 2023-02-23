#include <stdlib.h>
#include "minishell_struct.h"
#include "lexer.h"

void	free_minishell(t_minishell *minishell)
{
	ft_hm_clear(&minishell->env_variables, &free);
	ft_lstclear(&minishell->tokens, &free_token);
	ft_lst_of_lst_clear(&minishell->here_docs, &free);
}
