/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:14:45 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 06:09:50 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokens.h"
# include <stdbool.h>

// quote
int				remove_quotes(t_list *tokens);
int				is_valid_quote(char *command);

// simplify_tokens
//		add_command
//			add_path
//				absolute_path.c
bool			is_absolute_path(t_token *command, t_hashmap env_variables);
int				command_is_absolute_path(t_token *command);
//				add_path.c
int				add_path(t_token *command, t_hashmap env_variables);
//				builtin.c
enum e_builtin	is_builtin(char *command_name);
//				command.c
int				command_is_in_path(t_token *command, t_hashmap env_variables);
//			add_args.c
int				add_args(t_token *token, t_list **args);
//			add_command.c
t_token			*get_new_command(t_list **tokens, t_hashmap env_variables);
//			get_files.c
t_list			*get_files(t_list **files);
//		simplify_tokens.c
int				simplify_tokens(t_list **tokens, t_hashmap env_variables);

#endif
