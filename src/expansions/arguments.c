/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:48:12 by tdameros          #+#    #+#             */
/*   Updated: 2023/03/07 23:48:17 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "lexer.h"
#include "expansions.h"

static char		**get_args_array(t_list *arguments);
static int		cmp_quote_expansion(void *expansion_ptr);
static int		cmp_space_expansion(void *expansion_ptr);

int	apply_arguments_expansion(t_token *token, t_hashmap env_variables)
{
	t_list	*arguments;
	t_list	*argument;
	size_t	index;
	char	**args_array;

	arguments = NULL;
	index = 0;
	while (token->args[index] != NULL)
	{
		errno = 0;
		argument = get_str_expansion(token->args[index], env_variables);
		if (errno != 0)
			return (ft_lstclear(&arguments, free_expansion), -1);
		ft_lstadd_back(&arguments, argument);
		index++;
	}
	args_array = get_args_array(arguments);
	ft_lstclear(&arguments, free_expansion);
	if (args_array == NULL)
		return (-1);
	ft_free_split(token->args);
	token->args = args_array;
	return (0);
}

t_list	*get_str_expansion(char *argument, t_hashmap env_variables)
{
	t_list	*tokens;

	errno = 0;
	tokens = get_expansion_tokens(argument);
	if (errno != 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (replace_tildes(&tokens, env_variables) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (replace_parameters(&tokens, env_variables) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (merge_words(&tokens) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (split_words(&tokens) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (replace_wildcards(&tokens) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	if (add_empty_word_beetween_quotes(&tokens) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	ft_list_remove_if(&tokens, cmp_quote_expansion, free_expansion);
	if (merge_words(&tokens) < 0)
		return (ft_lstclear(&tokens, free_expansion), NULL);
	ft_list_remove_if(&tokens, cmp_space_expansion, free_expansion);
	return (tokens);
}

static char	**get_args_array(t_list *arguments)
{
	char		**args_array;
	t_expansion	*expansion;
	size_t		index;

	args_array = malloc(sizeof(*args_array) * (ft_lstsize(arguments) + 1));
	if (args_array == NULL)
		return (NULL);
	index = 0;
	while (arguments != NULL)
	{
		expansion = arguments->content;
		args_array[index] = ft_strdup(expansion->content);
		index++;
		arguments = arguments->next;
	}
	args_array[index] = NULL;
	return (args_array);
}

static int	cmp_quote_expansion(void *expansion_ptr)
{
	t_expansion	*expansion;

	expansion = expansion_ptr;
	return (!(expansion->type == DOUBLE_QUOTE
			|| expansion->type == SIMPLE_QUOTE));
}

static int	cmp_space_expansion(void *expansion_ptr)
{
	t_expansion	*expansion;

	expansion = expansion_ptr;
	return (!(expansion->type == SPACE));
}
