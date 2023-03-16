/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:41:29 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 18:05:52 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define IFS " \t"
# define COMMAND_NOT_FOUND "command not found"

# include "libft.h"

enum e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	OPERATOR = 2,
	PATH_FILE = 3,
	BUILTIN = 4,
	EXECUTABLE = 5,
	SUBSHELL = 6,
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
	ECHO_CMD = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	UNSET = 4,
	ENV = 5,
	EXIT = 6,
	ALIAS = 7,
	UNALIAS = 8,
};

typedef struct s_token
{
	enum e_type			type;
	enum e_operators	operator;
	enum e_builtin		builtin;
	char				*name;
	char				**args;
	t_list				*files;
	t_list				*subshell;
}	t_token;

//	identifier.c
enum e_type	identify_token(t_list *previous_tokens, char *command);
int			get_index_end_token(char *command);
int			get_index_next_token(char *command);

//	operator.c
int			get_operator(char *string);
int			add_operator_token(t_list **tokens, enum e_operators operator);
bool		is_file_operator_token(t_token *token);
bool		is_operator(char *command);

//	token.c
t_list		*get_tokens(char *command);
void		free_token(void *token);
t_token		*create_token(enum e_type type, enum e_operators operator,
				char *name);

#endif
