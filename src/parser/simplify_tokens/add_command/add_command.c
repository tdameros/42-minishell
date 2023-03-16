/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:14:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:50:40 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	seperate_command_elements(t_list **tokens, t_list **args,
				t_list **files);

t_token	*get_new_command(t_list **tokens)
{
	t_token	*new_command;
	t_list	*args;
	t_list	*files;

	new_command = ft_calloc(1, sizeof(*new_command));
	if (new_command == NULL)
		return (NULL);
	seperate_command_elements(tokens, &args, &files);
	new_command->files = get_files(&files);
	if (add_args(new_command, &args))
	{
		ft_lstclear(&args, &free_token);
		free_token(new_command);
		return (NULL);
	}
	new_command->operator = -1;
	return (new_command);
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
			return ;
		token = (*tokens)->content;
	}
}
