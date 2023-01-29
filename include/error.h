/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:06:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/01/28 22:07:05 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <string.h>
# include <errno.h>
# include "lexer.h"

# define PIPE_FAILED "pipe() failed"
# define FORK_FAILED "minishell_fork() failed"
# define PIPE_CLOSE_FAILED "close() failed on pipe"
# define FILE_CLOSE_FAILED "close() failed on file"
# define PIPE_DUP2_FAILED "dup2() failed on pipe"
# define FILE_DUP2_FAILED "dup2() failed on file"
# define BUILTIN_CLOSE_FAILED "dup() failed on builtin"
# define BUILTIN_DUP_FAILED "dup() failed on builtin"
# define BUILTIN_DUP2_FAILED "dup2() failed on builtin"

void	print_error(char *command, char *context, char *error);
char	*get_name(t_list *token);
char	*get_error(void);

#endif
