#include "libft.h"

bool	ft_is_in_set(char c, char *set)
{
	if (c == '\0')
		return (false);
	return (ft_strchr(set, c) != NULL);
}