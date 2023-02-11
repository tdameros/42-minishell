//
// Created by tdameros on 2/11/23.
//

#include <stdlib.h>
#include <unistd.h>
#include "readline/readline.h"
#include "libft.h"
#include "parser.h"
#include "lexer.h"
#include "get_here_docs.h"

static char *read_input(int *pipe_fd);
static char *get_input(void);

int run_new_interactive_parsing(char **command, t_list **parsed_tokens, t_list **here_docs)
{
    t_list  *tokens;
    int     return_code;
    char    *new_input;
    char    *new_command;

//    tokens = get_tokens(command);
//    if (tokens == NULL)
//        return (-1);
//    if (get_here_docs(here_docs, tokens) < 0)
//        return (-1);
    if (!is_valid_quote(*command))
    {
        new_input = get_input();
        if (ft_strlen(new_input) > 0)
        {
            tokens = get_tokens(new_input);
            get_here_docs(here_docs, tokens);
            ft_lstclear(&tokens, &free_token);
        }
        new_command = ft_strjoin_three(*command, "\n", new_input);
        free(*command);
        free(new_input);
        *command = new_command;
        return (run_new_interactive_parsing(command, parsed_tokens, here_docs));
    }
    tokens = get_tokens(*command);
    return_code = parse_syntax(tokens);
    ft_lstclear(&tokens, &free_token);
    if (return_code < 0)
        return (-1);
    else if (return_code == 0)
    {
        new_input = get_input();
        ft_printf("NEW INPUT : %s\n", new_input);
        if (ft_strlen(new_input) > 0)
        {
            tokens = get_tokens(new_input);
            get_here_docs(here_docs, tokens);
            ft_lstclear(&tokens, &free_token);
        }
        new_command = ft_strjoin_three(*command, " ", new_input);
        free(*command);
        free(new_input);
        *command = new_command;
        return (run_new_interactive_parsing(command, parsed_tokens, here_docs));
    }
    return (0);
}

static char *get_input(void)
{
    int		pipe_fd[2];
    pid_t	pid;
    char	*input;

    // TODO Make this work with ctrl c handling
    if (pipe(pipe_fd) == -1)
        return (NULL);
    pid = fork();
    if (pid == -1)
        return (NULL);
    if (pid != 0)
        return (read_input(pipe_fd));
    input = readline("> ");
    ft_putstr_fd(input, pipe_fd[1]);
    free(input);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    exit(0);
}

static char *read_input(int *pipe_fd)
{
    char	*input;

    close(pipe_fd[1]);
    input = get_next_line(pipe_fd[0]);
    close(pipe_fd[0]);
    return (input);
}
