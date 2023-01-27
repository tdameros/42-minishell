/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_forked_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:05:14 by vfries            #+#    #+#             */
/*   Updated: 2023/01/26 17:04:42 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	execute_command();

static enum e_operators	get_next_operator(t_list *tokens);
static t_list	*create_sub_tokens(t_list **tokens);

int	execute_forked_command(t_list **tokens, t_list_i **here_docs,
		t_hashmap env_variables)
{
	t_list *sub_tokens;
	(void)here_docs;
	(void)env_variables;
		print_tokens(*tokens);
	while (*tokens != NULL)
	{
		if (get_next_operator(*tokens) == PIPE)
		{
			ft_printf("== SUB_TOKENS ==\n");
			sub_tokens = create_sub_tokens(tokens);
			print_tokens(sub_tokens);
		}
		else
			*tokens = (*tokens)->next;
	}
	return (0);
}

static enum e_operators	get_next_operator(t_list *tokens)
{
	int		parentheses;
	t_token	*token;

	if (tokens == NULL)
		return (-1);
	parentheses = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type == OPERATOR)
			return (token->operator);
		tokens = tokens->next;
	}
	return (-1);
}

static t_list	*create_sub_tokens(t_list **tokens)
{
	t_list *sub_tokens;
	int		parentheses;
	t_token	*token;

	if (tokens == NULL)
		return (NULL);
	sub_tokens = NULL;
	parentheses = 0;
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type == OPERATOR && token->operator != PIPE)
			return (ft_lst_reverse(&sub_tokens));
		ft_lst_push(&sub_tokens, tokens);
	}
	return (ft_lst_reverse(&sub_tokens));
}

static void	get_next_command(t_list **tokens, t_list_i **here_docs)
{
	int		parentheses;
	t_token	*token;

	parentheses = 0;
	if (token->operator != OPEN_PARENTHESES)
		ft_lst_get_next_free_current(tokens, &free_token);
	while (*tokens != NULL)
	{
		token = (*tokens)->content;
		if (token->operator == OPEN_PARENTHESES)
			parentheses++;
		else if (token->operator == CLOSE_PARENTHESES)
			parentheses--;
		else if (parentheses == 0 && token->type != OPERATOR)
			return ;
		skip_here_docs(token, here_docs);
		ft_lst_get_next_free_current(tokens, &free_token);
	}
}

static void	skip_here_docs(t_token *command, t_list_i **here_docs)
{
	t_list	*cursor;
	t_token	*token;


	cursor = command->files;
	while (cursor != NULL)
	{
		token = cursor->content;
		if (token->operator == HERE_DOC)

	}
}
