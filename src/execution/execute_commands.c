/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:54:27 by vfries            #+#    #+#             */
/*   Updated: 2023/01/24 21:17:34 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "lexer.h"

static int	execute_commands_loop(t_list *tokens);
static enum e_operators	get_next_operator(t_list *tokens);
static int	execute_piped_command(t_list *tokens);
static int	execute_normal_command(t_list *tokens);
int	execute_builtin(t_token *token);
int	execute_subshell(t_list *tokens);
char	**get_envp(void);
int	execute_path_command(t_token *token);

void	get_next_command_to_run(t_list **tokens, enum e_operators operator,
								int last_exit_code);

int	execute_commands(t_list *tokens, t_list_i *here_docs)
{
	pid_t	pid;
	int		exit_code;

	(void) here_docs;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		exit_code = execute_commands_loop(tokens);
		// TODO free_all
		exit(exit_code);
	}
	wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}

static int	execute_commands_loop(t_list *tokens)
{
	enum e_operators	operator;
	int					last_exit_code;

	while (tokens != NULL)
	{
		operator = get_next_operator(tokens);
		if (operator == PIPE)
			last_exit_code = execute_piped_command(tokens);
		else
			last_exit_code = execute_normal_command(tokens);
		get_next_command_to_run(&tokens, operator, last_exit_code);
	}
	return (last_exit_code);
}

static enum e_operators	get_next_operator(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (-1);
	token = tokens->content;
	while (token->type != OPERATOR || token->operator == OPEN_PARENTHESES
		   || token->operator == CLOSE_PARENTHESES)
	{
		tokens = tokens->next;
		if (tokens == NULL)
			return (-1);
		token = tokens->content;
	}
	return (token->operator);
}

static int	execute_piped_command(t_list *tokens)
{
	pid_t	id;
	int		pipe_fd[2];
	int		command_exit_code;

	if (pipe(pipe_fd) == -1)
		return (-1);
	id = fork();
	if (id == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		// TODO free_all
		return (-1);
	}
	if (id == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		// TODO free_all
		execute_normal_command(tokens);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	wait(&command_exit_code);
	return (WEXITSTATUS(command_exit_code));
}

static int	execute_normal_command(t_list *tokens)
{
	t_token	*token;

	token = tokens->content;
	if (token->type == BUILTIN)
		return (execute_builtin(token));
	if (token->type == OPERATOR)
		return (execute_subshell(tokens));
	return (execute_path_command(token));
}

int	execute_builtin(t_token *token)
{
	//TODO DO BUILTINS
	(void) token;
	return (execute_path_command(token));
}

int	execute_subshell(t_list *tokens)
{
	//TODO
	(void) tokens;
	return (0);
}

char	**get_envp(void)
{
	return (ft_calloc(1, sizeof(char *)));
}

int	execute_path_command(t_token *token)
{
	pid_t	pid;
	int		command_exit_code;

	pid = fork();
	//TODO pid == -1
	if (pid == 0)
	{
		execve(token->name, token->args, get_envp());
		if (token->type == COMMAND)
			ft_printf("minishell: %s: command not found", token->args[0]);
		else
			ft_printf("minishell: %s: No such file or directory",
				token->args[0]);
		// TODO FIND RIGHT EXIT CODE
		exit(-1);
	}
	wait(&command_exit_code);
	return (WEXITSTATUS(command_exit_code));
}
