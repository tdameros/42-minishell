/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:18:49 by vfries            #+#    #+#             */
/*   Updated: 2023/02/08 18:13:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"

int	file_error(t_list **simplified_files, t_list *tokens);
void	print_file_error(t_list *tokens);

int	get_files(t_list **files, t_list **simplified_files, t_list **tokens)
{
	t_token	*file_token;
	t_token	*simplified_file_token;

	*simplified_files = NULL;
	while (*files != NULL)
	{
		ft_lst_push(simplified_files, files);
		if (*files == NULL)
			return (file_error(simplified_files, *tokens));
		file_token = (*files)->content;
		simplified_file_token = (*simplified_files)->content;
		if ((file_token->name == NULL && simplified_file_token->name == NULL)
			|| (file_token->name != NULL
				&& simplified_file_token->name != NULL))
			return (file_error(simplified_files, *tokens));
		if (file_token->name == NULL)
			simplified_file_token->operator = file_token->operator;
		else
		{
			simplified_file_token->name = file_token->name;
			file_token->name = NULL;
		}
		ft_lst_get_next_free_current(files, &free_token);
	}
	return (0);
}

int	file_error(t_list **simplified_files, t_list *tokens)
{
	ft_lstclear(simplified_files, &free_token);
	print_file_error(tokens);
	return (FILE_COUNT_IS_BAD);
}

void	print_file_error(t_list *tokens)
{
	t_token	*token;

	if (tokens == NULL)
		return (print_error(NULL, NULL,
				"syntax error near unexpected token `newline'"));
	token = tokens->content;
	if (token->operator == OPEN_PARENTHESES)
		print_error(NULL, NULL, "syntax error near unexpected token `('");
	else if (token->operator == CLOSE_PARENTHESES)
		print_error(NULL, NULL, "syntax error near unexpected token `)'");
	else if (token->operator == OR)
		print_error(NULL, NULL, "syntax error near unexpected token `||'");
	else if (token->operator == AND)
		print_error(NULL, NULL, "syntax error near unexpected token `&&'");
	else if (token->operator == PIPE)
		print_error(NULL, NULL, "syntax error near unexpected token `|'");
	else if (token->operator == INPUT_REDIRECT)
		print_error(NULL, NULL, "syntax error near unexpected token `<'");
	else if (token->operator == OUTPUT_REDIRECT)
		print_error(NULL, NULL, "syntax error near unexpected token `>'");
	else if (token->operator == HERE_DOC)
		print_error(NULL, NULL, "syntax error near unexpected token `<<'");
	else if (token->operator == APPEND)
		print_error(NULL, NULL, "syntax error near unexpected token `>>'");
}
