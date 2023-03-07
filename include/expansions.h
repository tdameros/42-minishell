/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:37:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/04 23:37:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include <dirent.h>

# include "libft.h"

# include "lexer.h"

//  lexer/
enum e_expansion_type
{
	WORD = 0,
	DOUBLE_QUOTE = 1,
	SIMPLE_QUOTE = 2,
	DOLLAR = 3,
	SPACE = 4,
	SLASH = 5,
	STAR = 6
};

typedef struct s_expansion
{
	enum e_expansion_type	type;
	char					*content;
}	t_expansion;

//	lexer/expressions.c
ssize_t	add_simple_quotes_expression(char *arg, t_list **expansions);
ssize_t	add_double_quotes_expression(char *arg, t_list **expansions);
ssize_t	add_dollar_expression(char *arg, t_list **expansions);
ssize_t	add_expression(char *arg, char *delimiters, t_list **expansions);

//	lexer/tokens.c
t_list	*get_expansion_tokens(char *arg);

//	lexer/utils.c
char	*get_end_expression(char *arg, char *delimiters);
char	*get_end_dollar_parameter(char *arg);
int		add_expansion_node(char *content, int type, t_list **expansions);
t_list	*create_expansion_node(char *content, int type);
void	free_expansion(void *expansion);

//	parameters/replace.c
int		replace_parameters(t_list **expansions, t_hashmap env_variables);

//	parameters/strdup_parameters.c
char	*strdup_with_parameters(char *string, t_hashmap env_variables);

//	paths/absolute_path.c
bool	is_absolute_path(t_token *command, t_hashmap env_variables);
int		command_is_absolute_path(t_token *command);

//	paths/add_path.c
int		add_path(t_token *command, t_hashmap env_variables);

//	paths/builtin.c
enum e_builtin	is_builtin(char *command_name);

//	paths/command.c
int		command_is_in_path(t_token *command, t_hashmap env_variables);

//	wildcards/

typedef struct s_path
{
	char	*absolute;
	char	*relative;
}	t_path;

//	wildcards/add.c
int		add_match_in_list(t_list **path_list, t_path path, t_list *pattern);

//	wildcards/list.c
t_list	*get_wildcards_list(t_list *pattern);

//	wildcards/match.c
int		is_wildcard_match(t_list *wildcards, char *string);

//	wildcards/lexer.c
t_list	*wildcards_lexer(t_list *expansions_tokens);

//	wildcards/replace.c
int		replace_wildcards(t_list **tokens);

// wildcards/slash.c
bool	is_slash_token(t_list *token);
t_list	*skip_slash_token(t_list *token);
t_list	*get_slash_token(t_list *token);

//	wildcards/utils.c
bool	ft_isdir(char *path, char *file_name);
void	free_path(t_path *path);
int		add_wildcard_with_space(char *content, int type, t_list **tokens);
bool	has_wildcard_in_pattern(t_list *pattern);

//







//	lexer/tokens.c
t_list			*get_expansion_tokens(char *arg);

//  lexer/expressions.c
ssize_t		add_simple_quotes_expression(char *arg, t_list **expansions);
ssize_t		add_dollar_expression(char *arg, t_list **expansions);
ssize_t		add_double_quotes_expression(char *arg, t_list **expansions);
ssize_t		add_expression(char *arg, char *delimiters, t_list **expansions);

//  lexer/utils.c
char    *get_end_expression(char *arg, char *delimiters);
char    *get_end_dollar_parameter(char *arg);
int     add_expansion_node(char *content, int type, t_list **expansions);
void	free_expansion(void *expansion);
t_list	*create_expansion_node(char *content, int type);
void    print_expansion_tokens(t_list *tokens);

int	apply_arguments_expansion(t_token *token, t_hashmap env_variables);

//	lexer/parameters.c
int		replace_parameters(t_list **expansions, t_hashmap env_variables);

int		merge_words(t_list **tokens);
int		split_words(t_list **tokens);
int	add_empty_word_beetween_quotes(t_list **tokens);

t_list *wildcards_lexer(t_list *expansions_tokens);
int		is_wilcard_match(t_list *wilcards, char *string);
int		replace_wildcards(t_list **tokens);
int	replace_tildes(t_list **tokens, t_hashmap env_variables);
t_list	*get_argument_expansion(char *argument, t_hashmap env_variables);
int	add_wildcard_with_space(char *content, int type, t_list **tokens);
bool	has_wildcard_in_pattern(t_list *pattern);

//  add_path/

//	absolute_path.c
bool			is_absolute_path(t_token *command, t_hashmap env_variables);
int				command_is_absolute_path(t_token *command);

//	add_path.c
int				add_path(t_token *command, t_hashmap env_variables);

//	builtin.c
enum e_builtin	is_builtin(char *command_name);

//	command.c
int				command_is_in_path(t_token *command, t_hashmap env_variables);

//	wildcards/


//	wildcards/add.c
int				add_match_in_list(t_list **path_list, t_path path,
					t_list *pattern);

//	wildcards/duplicate.c
char			**duplicate_args_with_wildcards(char **argument);

//	wildcards/list.c
t_list			*get_wildcards_list(t_list *pattern);

//	wildcards/match.c
int				is_match(char *pattern, char *string);

//	wildcards/utils.c
bool			ft_isdir(char *path, char *file_name);
void			free_path(t_path *path);
int				is_wildcard(char *pattern);
ssize_t			size_with_wildcards_args(char **arguments);
bool			is_slash_token(t_list *token);
t_list			*skip_slash_token(t_list *token);
t_list			*get_slash_token(t_list *token);

//	alias.c
int				replace_alias(char **args, t_hashmap alias_variables);

//	files.c
int				apply_files_expansion(t_list *files, t_hashmap env_variables);

//	here_docs.c
int				apply_here_docs_expansions(t_token *token, t_list *here_docs,
					t_hashmap env_variables);

//	parameters.c
int				insert_parameters_in_args(char **args, t_hashmap env_variables);
char			*strdup_with_parameters_quote(char *str,
					t_hashmap env_variables);
char			*strdup_with_parameters(char *string, t_hashmap env_variables);

//	parameters_utils.c
char			*get_parameter_value(char *parameter, t_hashmap env_variables);
char			*get_end_parameter(char *string);
bool			is_parameter(char *string, char quote);
char			get_current_quote(char *string, char *quote);

//	quotes.c
int				remove_quotes_in_args(char **args);
char			*strdup_without_quote(char *command);

//	token.c
int				apply_token_expansion(t_token *token, t_list *here_docs,
					t_hashmap env_variables);

//	words.c
char			**split_args(char **args);

#endif
