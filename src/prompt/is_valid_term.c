#include <stdbool.h>

#include "libft.h"

bool	is_valid_term(t_hashmap env_variables)
{
	const char	*accepted_terms[] = {"xterm-256color", "gnome-256color",
		"konsole-256color", "rxvt-unicode-256color", "konsole-16-color",
		"xterm", NULL};
	char		*term;

	term = ft_hm_get_content(env_variables, "TERM");
	return (ft_str_is_in_strs(term, (char **) accepted_terms));
}