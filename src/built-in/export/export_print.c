/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:10:44 by tdameros          #+#    #+#             */
/*   Updated: 2023/02/22 22:10:49 by tdameros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "env_variables.h"

static	int	print_env_variables_export(char **envp);

int	print_export(t_hashmap env_variables)
{
	char	**envp;

	if (ft_hm_size(env_variables) == 1)
		return (0);
	envp = get_all_envp(env_variables);
	if (envp == NULL)
		return (-1);
	if (ft_msort_str(envp, 0, ft_split_size(envp) - 1) < 0)
	{
		ft_free_split(envp);
		return (-1);
	}
	return (print_env_variables_export(envp));
}

static int	print_env_variables_export(char **envp)
{
	char	*equal;
	size_t	index;

	index = 0;
	while (envp[index] != NULL)
	{
		equal = ft_strchr(envp[index], '=');
		if (equal == NULL)
			ft_printf("declare -x %s\n", envp[index]);
		else
		{
			*equal = '\0';
			ft_printf("declare -x %s=\"%s\"\n", envp[index], equal + 1);
		}
		free(envp[index]);
		index++;
	}
	free(envp);
	return (0);
}
