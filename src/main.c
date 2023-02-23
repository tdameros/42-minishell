/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:07:30 by vfries            #+#    #+#             */
/*   Updated: 2023/02/23 02:04:22 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell_struct.h"
#include "error.h"
#include "run_minishellrc.h"
#include "minishell_signal.h"
#include "exit_code.h"
#include "env_variables.h"
#include "interactive.h"
#include "terminal.h"
#include "execute_single_line_command.h"

#define PROMPT "\e[32m➜ \e[36mminishell-1.0$ \x1b[0m"

#define FAILED_TO_SAVE_TERMINAL -2

static int	minishell_init(t_minishell *minishell, char **envp);
static int	run_shell(t_minishell *minishell, int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;
	int				tmp;

	tmp = minishell_init(&minishell, envp);
	if (tmp < 0)
	{
		print_error(NULL, "Failed to initialize minishell\n", get_error());
		ft_hm_clear(&minishell.env_variables, &free);
		if (tmp != FAILED_TO_SAVE_TERMINAL)
			terminal_restore(minishell.termios_save);
		return (1);
	}
	tmp = run_shell(&minishell, argc, argv);
	ft_hm_clear(&minishell.env_variables, &free);
	if (terminal_restore(minishell.termios_save) < 0)
		return (2);
	return (tmp);
}

static int	minishell_init(t_minishell *minishell, char **envp)
{
	ft_bzero(minishell, (sizeof * minishell));
	if (terminal_save(&minishell->termios_save) < 0)
		return (FAILED_TO_SAVE_TERMINAL);
	minishell->env_variables = get_env_variables(envp);
	if (minishell->env_variables == NULL
		|| signal_init_handling_outside_execution() < 0
		|| init_exit_code(minishell->env_variables) < 0
		|| terminal_disable_ctrl_backslash_output() < 0)
		return (-1);
	return (0);
}

static int	run_shell(t_minishell *minishell, int argc, char **argv)
{
	if (argc == 1 || ft_strcmp(argv[1], "-c") != 0)
	{
		run_minishellrc(minishell);
		return (run_interactive_shell(minishell));
	}
	else if (argc > 2)
		return (execute_single_line_command(minishell, argv[2]));
	print_error(NULL, "-c", "option requires an argument");
	return (2);
}

// TODO remove function below
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
