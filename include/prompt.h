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

char	*get_command_result(char *path, char **args, char **envp);

char	*get_git_branch(t_hashmap env_variables);

char	*get_prompt(t_hashmap env_variables);

#endif
