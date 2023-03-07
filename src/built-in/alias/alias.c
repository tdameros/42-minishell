#include <stdlib.h>

#include "libft.h"

#include "env_variables.h"
#include "error.h"
#include "exit_code.h"
#include "built_in.h"

static int	print_alias_variables(char **aliases);

static int	add_alias_variables(char **args, t_hashmap alias_variable);
static int	print_alias(t_hashmap alias);

int	alias(char **args, t_hashmap alias_variables)
{
	size_t	index;

	index = 1;
	if (args[index] == NULL)
	{
		if (print_alias(alias_variables) < 0)
		{
			print_error("alias", args[index], strerror(errno));
			return (exit_code(1));
		}
	}
	else
		return (exit_code(add_alias_variables(args + index, alias_variables)));
	return (exit_code(0));
}

static int	add_alias_variables(char **args, t_hashmap alias_variable)
{
	char	*value;
	char	*equal;

	while (*args != NULL)
	{
		equal = ft_strchr(*args, '=');
		if (equal == NULL)
			print_error("alias", *args, "not found");
		else
		{
			*equal = '\0';
			value = ft_strdup(equal + 1);
			if (value == NULL)
				return (-1);
			if (ft_hm_add_elem(alias_variable, *args, value, &free) < 0)
				return (free(value), -1);
		}
		args++;
	}
	return (0);
}

static int	print_alias(t_hashmap alias)
{
	char	**aliases;

	aliases = get_all_aliases(alias);
	if (aliases == NULL)
		return (-1);
	if (ft_msort_str(aliases, 0, ft_split_size(aliases) - 1) < 0)
	{
		ft_free_split(aliases);
		return (-1);
	}
	return (print_alias_variables(aliases));
}

static int	print_alias_variables(char **aliases)
{
	size_t	index;

	index = 0;
	while (aliases[index] != NULL)
	{
		ft_printf("alias %s\n", aliases[index]);
		free(aliases[index]);
		index++;
	}
	free(aliases);
	return (0);
}
