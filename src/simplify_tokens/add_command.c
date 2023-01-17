/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:14:16 by vfries            #+#    #+#             */
/*   Updated: 2023/01/17 17:57:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <unistd.h>
#include <stdlib.h>

static void	seperate_command_elements(t_list **tokens,
				t_list **args, t_list **files);
static void	push_command_in_parsed_tokens_and_reverse_args(
				t_list **parsed_tokens, t_list **args);
static void	simplify_files(t_list **files);
static char	**get_args_strs(t_list **args, t_list **parsed_tokens);

// TODO Delete me
int	is_file_operator_token(t_token *token)
{
	if (token == NULL || token->type != OPERATOR)
		return (0);
	return (token->operator == INPUT_REDIRECT
		|| token->operator == OUTPUT_REDIRECT
		|| token->operator == HERE_DOC
		|| token->operator == APPEND);
}
//!

void	add_command(t_list **parsed_tokens, t_list **tokens)
{
	t_list	*args;
	t_list	*files;

	seperate_command_elements(tokens, &args, &files);
	push_command_in_parsed_tokens_and_reverse_args(parsed_tokens, &args);
	((t_token *)(*parsed_tokens)->content)->args = get_args_strs(&args,
			parsed_tokens);
	simplify_files(&files);
	((t_token *)(*parsed_tokens)->content)->files = files;
}

static void	seperate_command_elements(t_list **tokens,
				t_list **args, t_list **files)
{
	*args = NULL;
	*files = NULL;
	while (*tokens != NULL && (((t_token *)(*tokens)->content)->type != OPERATOR
		|| is_file_operator_token((*tokens)->content)))
	{
		if (is_file_operator_token((*tokens)->content))
			ft_lst_push(files, tokens);
		else
			ft_lst_push(args, tokens);
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

static char	**get_args_strs(t_list **args, t_list **parsed_tokens)
{
	char	**args_strs;
	int		i;

	args_strs = malloc(sizeof(char *) * (ft_lstsize(*args) + 2));
	if (args_strs == NULL)
	{
		ft_lstclear(args, &free_token);
		return (NULL);
	}
	args_strs[0] = ((t_token *)(*parsed_tokens)->content)->name;
	((t_token *)(*parsed_tokens)->content)->name = NULL;
	i = 1;
	while (*args != NULL)
	{
		args_strs[i] = ((t_token *)(*args)->content)->name;
		((t_token *)(*args)->content)->name = NULL;
		*args = ft_lst_get_next_free_current(*args, &free_token);
		i++;
	}
	args_strs[i] = NULL;
	return (args_strs);
}
