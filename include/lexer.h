/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:38:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/23 13:38:00 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

enum e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	OPERATOR = 2,
	PATH_FILE = 3,
};

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

typedef struct s_token
{
	enum e_type			type;
	enum e_operators	operator;
	char				*name;
}	t_token;

t_list	*get_tokens(char *command);
void	free_token(void *token);
t_token	*create_token(enum e_type type, enum e_operators operator, char *name);
void	print_tokens(t_list *tokens);

int		get_operator(char *string);
int		add_operator_token(t_list **tokens, enum e_operators operator);
bool	is_file_operator_token(t_token *token);
bool	is_operator(char *command);

enum e_type	identify_token(t_list *previous_tokens, char *command);
int			get_index_end_token(char *command);
int			get_index_next_token(char *command);

int	is_match(char *pattern, char *string);
void	print_wildcard(char *pattern);
#endif
