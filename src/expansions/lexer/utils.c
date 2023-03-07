/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:28:00 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/06 18:28:00 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

char	*get_end_expression(char *arg, char *delimiters)
{
	while (*arg != '\0' && ft_strchr(delimiters, *arg) == NULL)
		arg++;
	return (arg);
}

char	*get_end_dollar_parameter(char *arg)
{
	if (ft_isdigit(*arg) || *arg == '?')
		return (arg);
	while (ft_isalnum(*arg) || *arg == '_')
		arg++;
	return (arg - 1);
}

int	add_expansion_node(char *content, int type, t_list **expansions)
{
	t_list	*new_node;

	new_node = create_expansion_node(content, type);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_back(expansions, new_node);
	return (0);
}

t_list	*create_expansion_node(char *content, int type)
{
	t_expansion	*new_expansion;
	t_list		*new_node;

	new_expansion = malloc(sizeof(*new_expansion));
	if (new_expansion == NULL)
		return (NULL);
	new_expansion->content = content;
	new_expansion->type = type;
	new_node = ft_lstnew(new_expansion);
	if (new_node == NULL)
	{
		free(new_expansion);
		return (NULL);
	}
	return (new_node);
}

void	free_expansion(void *expansion)
{
	t_expansion	*expansion_ptr;

	expansion_ptr = expansion;
	if (expansion_ptr != NULL)
		free(expansion_ptr->content);
	free(expansion_ptr);
}

void	print_expansion_tokens(t_list *tokens)
{
	t_expansion *expansion;

	while (tokens != NULL)
	{
		expansion = tokens->content;
		ft_printf("----------------------\n");
		if (expansion->type == DOLLAR)
			ft_printf("Type -> DOLLAR\n");
		else if (expansion->type == SIMPLE_QUOTE)
			ft_printf("Type -> SIMPLE_QUOTE\n");
		else if (expansion->type == DOUBLE_QUOTE)
			ft_printf("Type -> DOUBLE_QUOTE\n");
		else if (expansion->type == WORD)
			ft_printf("Type -> WORD\n");
		else if (expansion->type == SPACE)
			ft_printf("Type -> SPACE\n");
		else if (expansion->type == SLASH)
			ft_printf("Type -> SLASH\n");
		else if (expansion->type == STAR)
			ft_printf("Type -> STAR\n");
		if (expansion->content != NULL)
			ft_printf("Content / Len -> %s | %d\n", expansion->content, ft_strlen(expansion->content));
		else
			ft_printf("Content -> NULL\n");
		tokens = tokens->next;
	}
}
