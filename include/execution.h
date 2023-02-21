/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:34:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/19 22:34:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell_struct.h"
# include "lexer.h"

void	exec_free_minishell(t_minishell *minishell);

void	skip_tokens_here_docs(t_list *tokens, t_list **here_docs);
void	skip_token_here_docs(t_token *token, t_list **here_docs);
int		read_here_doc(t_list **here_docs);

void	execute_command(t_minishell *minishell, t_token *command, char **envp);

void	execute_command_no_pipe(t_minishell *minishell,
			bool is_last_piped_command);

pid_t	execute_piped_command(t_minishell *minishell,
			t_list **sub_tokens);

void	execute_pipes(t_minishell *minishell);

void	execute_commands(t_minishell *minishell);

int		save_io(char *command_name, int *io_save);
int		close_io_save(char *command_name, int *io_save);
int		restore_io_and_close_io_save(int *io_save, char *command_name);

int		open_and_dup_files(t_list *files, t_list *here_docs);

void	run_builtin(t_minishell *minishell, t_token *command);

#endif
