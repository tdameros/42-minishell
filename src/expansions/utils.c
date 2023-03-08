#include <stdlib.h>

#include "libft.h"

#include "expansions.h"

static t_list	*create_expansion_node(char *content, int type);

int	add_back_expansion_node(char *content, int type, t_list **expansions)
{
	t_list	*new_node;

	new_node = create_expansion_node(content, type);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_back(expansions, new_node);
	return (0);
}

int	add_front_expansion_node(char *content, int type, t_list **expansions)
{
	t_list	*new_node;

	new_node = create_expansion_node(content, type);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_front(expansions, new_node);
	return (0);
}

static t_list	*create_expansion_node(char *content, int type)
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
