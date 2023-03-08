/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:48:00 by tomy              #+#    #+#             */
/*   Updated: 2023/03/05 23:49:18 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

// add_directory_path.c
int		add_directory_path(t_list **prompt, t_hashmap env_variables,
			bool colored_prompt);

// add_elem_to_prompt.c
int		add_elem_to_prompt(t_list **prompt, char *elem);

// add_git_branch.c
int		add_git_branch(t_list **prompt, t_hashmap env_variables,
			bool colored_prompt);

// get_command_result.c
char	*get_command_result(char *path, char **args, char **envp);

// get_prompt.c
char	*get_prompt(t_hashmap env_variables);

bool	is_valid_term(t_hashmap env_variables);

#endif
