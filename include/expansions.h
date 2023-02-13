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

//	add_path/

//	absolute_path.c
bool	is_absolute_path(t_token *command, t_hashmap env_variables);
int		command_is_absolute_path(t_token *command);

//	add_path.c
int		add_path(t_token *command, t_hashmap env_variables);

//	builtin.c
enum e_builtin	is_builtin(char *command_name);

//	command.c
int		command_is_in_path(t_token *command, t_hashmap env_variables);

//	wildcards/

typedef struct s_path
{
	char	*absolute;
	char	*relative;
}	t_path;

//	wildcards/add.c
int		add_match_in_list(t_list **path_list, t_path path, char *pattern);

//	wildcards/duplicate.c
char	**duplicate_args_with_wildcards(char **argument);

//	wildcards/list.c
t_list	*get_wildcards_list(char *pattern);

//	wildcards/match.c
int		is_match(char *pattern, char *string);

//	wildcards/utils.c
bool	ft_isdir(char *path, char *file_name);
void	free_path(t_path *path);
int		is_wildcard(char *pattern);
ssize_t	size_with_wildcards_args(char **arguments);

//	alias.c
int		replace_alias(char **args, t_hashmap alias_variables);

//	files.c
int		apply_files_expansion(t_list *files, t_hashmap env_variables);

//	here_docs.c
int		apply_here_docs_expansions(t_token *token, t_list *here_docs, t_hashmap env_variables);

//	parameters.c
int		insert_parameters_in_args(char **args, t_hashmap env_variables);
char	*strdup_with_parameters_quote(char *string, t_hashmap env_variables);
char	*strdup_with_parameters(char *string, t_hashmap env_variables);

//	parameters_utils.c
char	*get_parameter_value(char *parameter, t_hashmap env_variables);
char	*get_end_parameter(char *string);
bool	is_parameter(char *string);
char	get_current_quote(char *string, char *quote);

//	quotes.c
int		remove_quotes_in_args(char **args);
char	*strdup_without_quote(char *command);

//	token.c
int		apply_token_expansion(t_token *token, t_list *here_docs, t_hashmap env_variables);

//	words.c
char	**split_args(char **args);


#endif
