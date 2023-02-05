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

# include "libft.h"
# include "lexer.h"

int	replace_alias(char **args, t_hashmap alias_variables);

int	insert_parameters_in_args(char **args, t_hashmap env_variables);
char	*strdup_with_parameters_quote(char *string, t_hashmap env_variables);
char	*strdup_with_parameters(char *string, t_hashmap env_variables);

char	*get_parameter_value(char *parameter, t_hashmap env_variables);
char	*get_end_parameter(char *string);
bool	is_parameter(char *string);
char	get_current_quote(char *string, char *quote);

int	remove_quotes_in_args(char **args);
char	*strdup_without_quote(char *command);

char	**split_args(char **args);

int	apply_expansions_before_exec(t_token *token, t_hashmap env_variables);
#endif
