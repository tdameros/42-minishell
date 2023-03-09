/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:14:45 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 05:34:06 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# include "lexer.h"

//	simplify_tokens/add_command/add_args.c
int		add_args(t_token *token, t_list **args);

//	simplify_tokens/add_command/add_command.c
t_token	*get_new_command(t_list **tokens);

//	simplify_tokens/add_command/get_files.c
t_list	*get_files(t_list **files);

//	simplify_tokens/get_subshells.c
t_list	*get_subshells(t_list *tokens);

//	simplify_tokens/simplify_tokens.c
int		simplify_tokens(t_list **tokens);

//	parse_tokens.c
int		parse_tokens(t_list	**tokens);

//	quotes.c
int		is_valid_quote(char *command);

//	syntax.c
int		parse_syntax(t_list *tokens);

#endif
