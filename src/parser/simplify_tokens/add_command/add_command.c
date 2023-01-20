/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:14:16 by vfries            #+#    #+#             */
/*   Updated: 2023/01/20 09:01:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "lexer.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>

static void	seperate_command_elements(t_list **tokens,
				t_list **args, t_list **files);
static void	push_command_in_parsed_tokens_and_reverse_args(
				t_list **parsed_tokens, t_list **args);
static void	simplify_files(t_list **files);
static bool	fix_parsed_tokens_equals_null(t_list **parsed_tokens,
				t_list **args, t_list **files);

bool	add_command(t_list **parsed_tokens, t_list **tokens,
			t_hashmap env_variables)
{
	t_list	*args;
	t_list	*files;

	seperate_command_elements(tokens, &args, &files);
	push_command_in_parsed_tokens_and_reverse_args(parsed_tokens, &args);
	if (*parsed_tokens == NULL
		&& fix_parsed_tokens_equals_null(parsed_tokens, &args, &files))
		return (true);
	((t_token *)(*parsed_tokens)->content)->args = get_args_strs(&args,
			parsed_tokens);
	simplify_files(&files);
	((t_token *)(*parsed_tokens)->content)->files = files;
	((t_token *)(*parsed_tokens)->content)->name = get_command_path(
			&((t_token *)(*parsed_tokens)->content)->type,
			((t_token *)(*parsed_tokens)->content)->args, env_variables);
	if (((t_token *)(*parsed_tokens)->content)->name == NULL)
		return (true);
	return (false);
}

static void	seperate_command_elements(t_list **tokens, t_list **args,
				t_list **files)
{
	*args = NULL;
	*files = NULL;
	while (*tokens != NULL && (((t_token *)(*tokens)->content)->type != OPERATOR
		|| is_file_operator_token((*tokens)->content)))
	{
		if (((t_token *)(*tokens)->content)->type == ARGUMENT
			|| ((t_token *)(*tokens)->content)->type == COMMAND)
			ft_lst_push(args, tokens);
		else
			ft_lst_push(files, tokens);
	}
}

static void	push_command_in_parsed_tokens_and_reverse_args(
				t_list **parsed_tokens, t_list **args)
{
	t_list	*reversed_args;

	reversed_args = NULL;
	while (*args != NULL)
	{
		if (((t_token *)(*args)->content)->type == COMMAND)
			ft_lst_push(parsed_tokens, args);
		else
			ft_lst_push(&reversed_args, args);
	}
	*args = reversed_args;
}

static void	simplify_files(t_list **files)
{
	t_list	*simplified_files;

	simplified_files = NULL;
	while (*files != NULL)
	{
		ft_lst_push(&simplified_files, files);
		if (*files == NULL)
		{
			ft_putstr_fd("ERROR: simplify_files()\n: files number is odd",
				STDERR_FILENO);
			break ;
		}
		if (((t_token *)(*files)->content)->name == NULL)
			((t_token *)simplified_files->content)->operator
				= ((t_token *)(*files)->content)->operator;
		else
			((t_token *)simplified_files->content)->name
				= ((t_token *)(*files)->content)->name;
		*files = ft_lst_get_next_free_current(*files, &free_token);
	}
	*files = simplified_files;
}

static bool	fix_parsed_tokens_equals_null(t_list **parsed_tokens,
				t_list **args, t_list **files)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (tmp != NULL)
	{
		ft_bzero(tmp, sizeof(t_token));
		tmp->type = COMMAND;
		*parsed_tokens = ft_lstnew(tmp);
	}
	if (*parsed_tokens == NULL)
	{
		free(tmp);
		ft_lstclear(args, &free_token);
		ft_lstclear(files, &free_token);
		return (true);
	}
	return (false);
}
