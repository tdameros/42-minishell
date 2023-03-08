/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:52:00 by vfries            #+#    #+#             */
/*   Updated: 2023/03/07 16:52:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_struct.h"
#include "exit_code.h"

int	which(char **argv, t_minishell *minishell)
{
	size_t	i;
	int		ret;

	if (*argv == NULL)
		return (exit_code(1));
	ret = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		if (print_path_to_command(argv[i], minishell))
			ret = 1;
		i++;
	}
	return (exit_code(ret));
}

static int	print_path_to_command(char *command, t_minishell *minishell)
{
	char	*hashmap_content;

	hashmap_content = ft_hm_get_content(minishell->alias, command);
	if (hashmap_content != NULL)
	{
		ft_printf("%s: aliased to %s", command, hashmap_content);
		return (0);
	}

}
