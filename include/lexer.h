/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:17:02 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 04:21:48 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "tokens.h"
# include "libft.h"

int		get_operator(char *string);
t_token	*create_token(enum e_type type, enum e_operators operator, char *name);
int		add_operator_token(t_list **tokens, enum e_operators operator);
int		is_file_operator_token(t_token *token);

#endif