/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/02/14 22:54:32 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_struct.h"
#include "error.h"
#include "minishell_signal.h"
#include "exit_code.h"
#include "env_variables.h"
#include "interactive.h"
#include "terminal.h"

#define PROMPT "\e[32m➜ \e[36mminishell-1.0$ \x1b[0m"

#define FAILED_TO_SAVE_TERMINAL -2

static int	minishell_init(t_minishell *minishell, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;
	int				tmp;

	(void)argc;
	(void)argv;
	tmp = minishell_init(&minishell, envp);
	if (tmp < 0)
	{
		print_error(NULL, "Failed to initialize minishell\n", get_error());
		ft_hm_clear(&minishell.env_variables, &free);
		if (tmp != FAILED_TO_SAVE_TERMINAL)
			terminal_restore(minishell.termios_save);
		return (1);
	}
	tmp = run_interactive_shell(&minishell);
	if (terminal_restore(minishell.termios_save) < 0)
		return (2);
	return (tmp);
}

static int	minishell_init(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, (sizeof minishell));
	if (terminal_save(&minishell->termios_save) < 0)
		return (FAILED_TO_SAVE_TERMINAL);
	minishell->env_variables = get_env_variables(envp);
	if (minishell->env_variables == NULL || signal_init_handling() < 0
		|| init_exit_code(minishell->env_variables) < 0
		|| terminal_disable_ctrl_backslash_output() < 0)
		return (-1);
	return (0);
}

void	print_here_docs(t_list *here_docs)
{
	t_list	*cursor;
	int		i;

	i = 0;
	ft_printf("========= HERE DOCS ==========\n");
	while (here_docs != NULL)
	{
		ft_printf("========= HERE DOC %d ==========\n", i);
		ft_printf("         (Reversed)\n");
		cursor = here_docs->content;
		// ft_printf("%c", ((char *)cursor->content)[0]);
		while (cursor != NULL)
		{
			ft_printf("%s", cursor->content);
			cursor = cursor->next;
		}
		here_docs = here_docs->next;
		i++;
	}
}
