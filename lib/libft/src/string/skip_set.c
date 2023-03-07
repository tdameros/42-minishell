#include "libft.h"

char	*ft_skip_set(const char *str, const char *set)
{
	if (*set == '\0')
		return ((char *) str);
	while (ft_strchr(set, *str) != NULL)
		str++;
	return ((char *) str);
}