/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_term.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 01:52:57 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 01:53:03 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_valid_term(t_hashmap env_variables)
{
	const char	*accepted_terms[] = {"xterm-256color", "gnome-256color",
		"konsole-256color", "rxvt-unicode-256color", "konsole-16-color",
		"xterm", NULL};
	char		*term;

	term = ft_hm_get_content(env_variables, "TERM");
	return (ft_str_is_in_strs(term, (char **) accepted_terms));
}
