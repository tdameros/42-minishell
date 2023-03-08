/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:40:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/06 02:30:16 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "exit_code.h"
#include "prompt.h"
#include "env_variables.h"

#define ARROW "\001❯\002"

static int	add_arrow(t_list **prompt, bool colored_prompt);

char	*get_prompt(t_hashmap env_variables)
{
	bool	colored_prompt;
	t_list	*prompt;
	char	*prompt_str;

	colored_prompt = is_valid_term(env_variables);
	prompt = NULL;
	if (add_directory_path(&prompt, env_variables, colored_prompt) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (add_git_branch(&prompt, env_variables, colored_prompt) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (add_arrow(&prompt, colored_prompt) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (colored_prompt && add_elem_to_prompt(&prompt, ft_strdup(RESET_COLOR))
		< 0)
		return (ft_lstclear(&prompt, &free), NULL);
	prompt_str = ft_lst_join_strs(ft_lst_reverse(&prompt));
	ft_lstclear(&prompt, &free);
	return (prompt_str);
}

static int	add_arrow(t_list **prompt, bool colored_prompt)
{
	char	*arrow;

	if (colored_prompt == false)
		arrow = ft_strdup("> ");
	else if (exit_code(GET) != 0)
		arrow = ft_strjoin_three(RED, ARROW, " ");
	else
		arrow = ft_strjoin_three(PURPLE_BOLD_HIGH_INTENSITY, ARROW, " ");
	return (add_elem_to_prompt(prompt, arrow));
}
