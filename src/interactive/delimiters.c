#include "lexer.h"

static int	erase_quotes(char *command);

int	remove_quotes_in_delimiter(char *command)
{
	command = ft_skip_set(command, IFS);
	while (*command != '\0')
	{
		if (get_operator(command) == HERE_DOC)
		{
			command += 2;
			command = ft_skip_set(command, IFS);
			erase_quotes(command);
		}
		command += get_index_next_token(command);
	}
	return (0);
}

static int	erase_quotes(char *command)
{
	while (*command != '\0' && *command != ' ' && get_operator(command) < 0)
	{
		if (*command == '"' || *command == '\'')
			*command = '`';
		command++;
	}
	return (0);
}
