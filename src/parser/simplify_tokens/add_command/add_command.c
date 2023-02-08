/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:14:00 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 18:34:40 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "error.h"

static void	seperate_command_elements(t_list **tokens, t_list **args,
				t_list **files);

int	get_new_command(t_list **tokens, t_hashmap env_variables,
		t_token **new_command)
{
	t_list	*args;
	t_list	*files;

	*new_command = ft_calloc(1, sizeof(**new_command));
	if (*new_command == NULL)
		return (MALLOC_FAILED);
	seperate_command_elements(tokens, &args, &files);
	if (get_files(&files, &(*new_command)->files, tokens))
	{
		free_token(*new_command);
		ft_lstclear(&args, &free_token);
		*new_command = NULL;
		return (FILE_COUNT_IS_BAD);
	}
	if (add_args(*new_command, &args) || add_path(*new_command, env_variables))
	{
		ft_lstclear(&args, &free_token);
		free_token(*new_command);
		*new_command = NULL;
		return (MALLOC_FAILED);
	}
	(*new_command)->operator = -1;
	return (0);
}

static void	seperate_command_elements(t_list **tokens, t_list **args,
				t_list **files)
{
	t_token	*token;

	*args = NULL;
	*files = NULL;
	if (*tokens == NULL)
		return ;
	token = (*tokens)->content;
	while (token->type != OPERATOR || is_file_operator_token(token))
	{
		if (token->type == ARGUMENT || token->type == COMMAND)
			ft_lst_push(args, tokens);
		else
			ft_lst_push(files, tokens);
		if (*tokens == NULL)
			break ;
		token = (*tokens)->content;
	}
	ft_lst_reverse(files);
}
