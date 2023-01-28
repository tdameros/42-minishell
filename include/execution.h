/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomy <tomy@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:02:00 by tomy              #+#    #+#             */
/*   Updated: 2023/01/28 01:02:00 by tomy             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "libft.h"

void	execute_command(t_list *command, t_hashmap env_variables,
			t_list *here_docs, int env_modifs);
#endif