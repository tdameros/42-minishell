/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:14:45 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 09:02:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

// quote
int		remove_quotes(t_list *tokens);
int		is_valid_quote(char *command);

// simplify_tokens
void	simplify_tokens(t_list **tokens, t_hashmap env_variables);
//		add_command
char	**get_args_strs(t_list **args, t_list **parsed_tokens);
char	*get_command_path(enum e_type *token_type, char **args,
			t_hashmap env_variables);
bool	add_command(t_list **parsed_tokens, t_list **tokens,
			t_hashmap env_variables);
char	*command_is_in_path(char *command, t_hashmap env_variables);

#endif
