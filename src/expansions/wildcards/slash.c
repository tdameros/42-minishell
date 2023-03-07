#include "expansions.h"

bool	is_slash_token(t_list *token)
{
	t_expansion	*expansion;

	if (token == NULL)
		return (false);
	expansion = token->content;
	if (expansion == NULL)
		return (false);
	return (expansion->type == SLASH);
}

t_list	*skip_slash_token(t_list *token)
{
	while (is_slash_token(token))
		token = token->next;
	return (token);
}

t_list	*get_slash_token(t_list *token)
{
	while (token != NULL)
	{
		if (is_slash_token(token))
			return (token);
		token = token->next;
	}
	return (NULL);
}
