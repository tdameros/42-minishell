/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:08:31 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 06:08:39 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"

enum e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	OPERATOR = 2,
	PATH_FILE = 3,
	BUILTIN = 4,
	EXECUTABLE = 5,
};

// EXECUTABLE is used to change error msg when execve fails:
//		COMMAND:	"bash: CMD: command not found"
//		EXECUTABLE:	"bash: EXE: No such file or directory"

enum e_operators
{
	OPEN_PARENTHESES = 0,
	CLOSE_PARENTHESES = 1,
	OR = 2,
	AND = 3,
	PIPE = 4,
	INPUT_REDIRECT = 5,
	OUTPUT_REDIRECT = 6,
	HERE_DOC = 7,
	APPEND = 8,
};

enum e_builtin
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	UNSET = 4,
	ENV = 5,
	EXIT = 6,
};

typedef struct s_token
{
	enum e_type			type;
	enum e_operators	operator;
	enum e_builtin		builtin;
	char				*name;
	char				**args;
	t_list				*files;
}	t_token;

void	print_tokens(t_list *tokens);
t_list	*get_tokens(char *command);
void	free_token(void *token);

#endif
