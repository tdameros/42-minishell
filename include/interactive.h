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

//	here_docs.c
int		get_here_docs(t_list *tokens, t_minishell *minishell);

//	here_docs_syntax.c
int		get_here_docs_if_valid_syntax(char *command, char *complete_command,
			t_minishell *minishell);

//	input.c
int		get_input_command(char **command, char *join, t_minishell *minishell);

//	parsing.c
int		run_interactive_parsing(char **command, t_minishell *minishell);

//	shell.c
int		run_interactive_shell(t_minishell *minishell);

//	utils.c
void	close_pipe(int *fd);

#endif
