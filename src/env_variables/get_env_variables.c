#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"

#include "error.h"

#define SHLVL_LIMIT 1000

static int	add_envp_in_hashmap(char **envp, t_hashmap env_variables);
static int	add_variable_in_hashmap(char *env_variable,
				t_hashmap env_variables);
static int	add_shlvl_variable(t_hashmap env_variables);
static int	add_default_variables(char *minishell_path,
				t_hashmap env_variables);

t_hashmap	get_env_variables(char **envp, char *minishell_path)
{
	t_hashmap	env_variables;

	env_variables = ft_hm_init();
	if (env_variables == NULL)
		return (NULL);
	if (add_envp_in_hashmap(envp, env_variables) < 0)
		return (ft_hm_clear(&env_variables, &free), NULL);
	if (add_default_variables(minishell_path, env_variables) < 0)
		return (ft_hm_clear(&env_variables, &free), NULL);
	return (env_variables);
}

static int	add_envp_in_hashmap(char **envp, t_hashmap env_variables)
{
	while (*envp != NULL)
	{
		if (add_variable_in_hashmap(*envp, env_variables) < 0)
			return (-1);
		envp++;
	}
	return (0);
}

static int	add_variable_in_hashmap(char *env_variable, t_hashmap env_variables)
{
	char	*equal;
	char	*value;

	equal = ft_strchr(env_variable, '=');
	if (equal != NULL)
	{
		*equal = '\0';
		value = ft_strdup(equal + 1);
		if (value == NULL)
		{
			*equal = '=';
			return (-1);
		}
		if (ft_hm_add_elem(env_variables, env_variable, value, &free) < 0)
		{
			free(value);
			*equal = '=';
			return (-1);
		}
		*equal = '=';
	}
	return (0);
}

static int	add_default_variables(char *minishell_path, t_hashmap env_variables)
{
	char				*value;
	struct stat			stat_ptr;

	if (ft_hm_add_elem(env_variables, "SHELL", minishell_path, &free) < 0)
		return (free(minishell_path), -1);
	if (add_shlvl_variable(env_variables) < 0)
		return (-1);
	value = ft_hm_get_content(env_variables, "OLDPWD");
	if (value == NULL
		|| (stat(value, &stat_ptr) != 0 && (stat_ptr.st_mode & S_IFDIR) == 0))
	{
		if (ft_hm_add_elem(env_variables, "OLDPWD", NULL, &free) < 0)
			return (-1);
	}
	value = getcwd(NULL, 0);
	if (value == NULL)
	{
		print_error("shell-init", "getcwd", "cannot access parent directories");
		return (0);
	}
	if (ft_hm_add_elem(env_variables, "PWD", value, &free) < 0)
		return (free(value), -1);
	return (0);
}

static int	add_shlvl_variable(t_hashmap env_variables)
{
	char	*value;
	int		shlvl;

	value = ft_hm_get_content(env_variables, "SHLVL");
	if (value == NULL)
		shlvl = 1;
	else
		shlvl = ft_atoi(value) + 1;
	if (shlvl >= SHLVL_LIMIT)
	{
		print_error(NULL, "warning", "shell level too high, resetting to 1");
		shlvl = 1;
	}
	value = ft_itoa(shlvl);
	if (value == NULL)
		return (-1);
	if (ft_hm_add_elem(env_variables, "SHLVL", value, &free) < 0)
	{
		free(value);
		return (-1);
	}
	return (0);
}
