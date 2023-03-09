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

//	exec_here_docs_tools.c
void	skip_tokens_here_docs(t_list *tokens, t_list **here_docs);
void	skip_token_here_docs(t_token *token, t_list **here_docs);
int		read_here_doc(t_minishell *minishell);

//	execute_command.c
void	execute_command(t_minishell *minishell, t_token *command, char **envp);

//	execute_command_no_pipe.c
void	execute_command_no_pipe(t_minishell *minishell,
			bool is_last_piped_command);

//	execute_piped_command.c
pid_t	execute_piped_command(t_minishell *minishell,
			t_list **sub_tokens);

//	execute_pipes.c
void	execute_pipes(t_minishell *minishell);

//	execution.c
void	execute_commands(t_minishell *minishell);

//	io_save.c
int		save_io(char *command_name, int *io_save);
int		close_io_save(char *command_name, int *io_save);
int		restore_io_and_close_io_save(int *io_save, char *command_name);

//	open_and_dup_files.c
int		open_and_dup_files(t_list *files, t_minishell *minishell);

//	run_builtin.c
void	run_builtin(t_minishell *minishell, t_token *command);

#endif
