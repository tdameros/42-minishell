/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:38:00 by tomy              #+#    #+#             */
/*   Updated: 2023/02/14 22:54:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIVE_H
# define INTERACTIVE_H

# include "libft.h"
# include "minishell_struct.h"

int	get_input_command(char **command, char *join, t_list **here_docs);
int	run_interactive_parsing(char **command, t_minishell *minishell);

int	run_interactive_shell(t_minishell *minishell);

#endif
