/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:38:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/12 16:38:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIVE_H
# define INTERACTIVE_H

# include "libft.h"

int	get_input_command(char **command, char *join, t_list **here_docs);
int	run_new_interactive_parsing(char **command, t_list **parsed_tokens, t_list **here_docs);

int	run_interactive_shell(t_hashmap env_variables);
#endif