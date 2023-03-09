/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:18:49 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:50:45 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*get_files(t_list **files)
{
	t_list	*simplified_files;
	t_token	*file_token;
	t_token	*simplified_file_token;

	simplified_files = NULL;
	while (*files != NULL)
	{
		ft_lst_push(&simplified_files, files);
		file_token = (*files)->content;
		simplified_file_token = simplified_files->content;
		if (file_token->name == NULL)
			simplified_file_token->operator = file_token->operator;
		else
		{
			simplified_file_token->name = file_token->name;
			file_token->name = NULL;
		}
		ft_lst_get_next_free_current(files, &free_token);
	}
	return (simplified_files);
}
