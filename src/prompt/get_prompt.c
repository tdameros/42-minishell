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

#define BLACK "\001\e[0;30m\002"
#define BLACK_HIGH_INTENSITY "\001\e[0;90m\002"

#define RED "\001\e[0;31m\002"

#define GREEN "\001\e[0;32m\002"

#define YELLOW "\001\e[0;33m\002"

#define BLUE "\001\e[0;34m\002"
#define BLUE_HIGH_INTENSITY "\001\e[0;94m\002"

#define PURPLE "\001\e[0;35m\002"
#define PURPLE_BOLD "\001\e[1;35m\002"
#define PURPLE_BOLD_HIGH_INTENSITY "\001\e[1;95m\002"

#define CYAN "\001\e[0;36m\002"
#define CYAN_HIGH_INTENSITY "\001\e[0;96m\002"

#define WHITE "\001\e[0;37m\002"

#define RESET "\001\e[m\002"

#define ARROW "\001❯\002"

static int	add_directory_path(t_list **prompt, t_hashmap env_variables);
static int	add_git_branch(t_list **prompt, t_hashmap env_variables);
static int	add_arrow(t_list **prompt);
static int	add_elem_to_prompt(t_list **prompt, char *elem);

char	*get_prompt(t_hashmap env_variables)
{
	t_list	*prompt;
	char	*prompt_str;

	prompt = NULL;
	if (add_directory_path(&prompt, env_variables) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (add_git_branch(&prompt, env_variables) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (add_arrow(&prompt) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	if (add_elem_to_prompt(&prompt, ft_strdup(RESET)) < 0)
		return (ft_lstclear(&prompt, &free), NULL);
	prompt_str = ft_lst_join_strs(ft_lst_reverse(&prompt));
	ft_lstclear(&prompt, &free);
	return (prompt_str);
}

static int	add_directory_path(t_list **prompt, t_hashmap env_variables)
{
	char	*home_dir;
	char	*cwd;
	char	*result;
	size_t	home_dir_len;

	if (ft_hm_get_content(env_variables, "PWD") != NULL)
		cwd = ft_strdup(ft_hm_get_content(env_variables, "PWD"));
	else
		cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (-1);
	home_dir = ft_hm_get_content(env_variables, "HOME");
	if (home_dir != NULL)
		home_dir_len = ft_strlen(home_dir);
	if (home_dir != NULL && *home_dir != '\0' && *cwd != '\0'
		&& ft_strncmp(cwd, home_dir, home_dir_len) == 0)
	{
		cwd[0] = '~';
		ft_strlcpy(cwd + 1, cwd + home_dir_len, ft_strlen(cwd) + 1 - 1);
	}
	result = ft_strjoin_three(BLUE_HIGH_INTENSITY, cwd, " ");
	free(cwd);
	return (add_elem_to_prompt(prompt, result));
}

static int	add_git_branch(t_list **prompt, t_hashmap env_variables)
{
	char	*git_branch;

	git_branch = get_git_branch(env_variables);
	if (git_branch == NULL)
		return (0);
	if (add_elem_to_prompt(prompt, ft_strdup(BLACK_HIGH_INTENSITY)) < 0)
		return (-1);
	if (add_elem_to_prompt(prompt, git_branch) < 0)
		return (-1);
	return (add_elem_to_prompt(prompt, ft_strdup(" ")));
}

static int	add_arrow(t_list **prompt)
{
	char	*arrow;

	if (exit_code(GET) != 0)
		arrow = ft_strjoin_three(RED, ARROW, " ");
	else
		arrow = ft_strjoin_three(PURPLE_BOLD_HIGH_INTENSITY, ARROW, " ");
	return (add_elem_to_prompt(prompt, arrow));
}

static int	add_elem_to_prompt(t_list **prompt, char *elem)
{
	t_list	*new_node;

	if (elem == NULL)
		return (-1);
	new_node = ft_lstnew(elem);
	if (new_node == NULL)
	{
		free(elem);
		return (-1);
	}
	ft_lstadd_front(prompt, new_node);
	return (0);
}
