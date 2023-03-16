/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_line_command.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:49:43 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 19:43:08 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_SINGLE_LINE_COMMAND_H
# define EXECUTE_SINGLE_LINE_COMMAND_H

# include "minishell_struct.h"

int	execute_single_line_command(t_minishell *minishell, char *line);

#endif
