NAME			=	minishell


SRC_PATH		=	src/

SRC				=\
	built-in/cd.c						\
	built-in/echo.c						\
	built-in/env.c						\
	built-in/exit.c						\
	built-in/export.c					\
	built-in/pwd.c						\
	built-in/unset.c					\
\
\
	env_variables/get_env_variables.c	\
	env_variables/get_envp.c			\
	env_variables/print_env_variables.c	\
\
\
	execution/exec_here_docs_tools.c	\
	execution/execute_command.c			\
	execution/execute_pipes.c			\
	execution/execution.c				\
	execution/get_next.c				\
	execution/open_and_dup_files.c		\
	execution/run_builtin.c				\
\
\
	expansions/alias.c				\
	expansions/parameters.c			\
	expansions/parameters_utils.c	\
	expansions/quotes.c				\
	expansions/words.c				\
	expansions/before_execution.c	\
	expansions/wildcards/add.c		\
	expansions/wildcards/insert.c	\
	expansions/wildcards/list.c		\
	expansions/wildcards/match.c	\
	expansions/wildcards/utils.c	\
\
\
	error/error.c	\
\
\
	lexer/identifier.c \
	lexer/operator.c	\
	lexer/token.c		\
\
\
	parser/quote/valid.c	\
\
	parser/simplify_tokens/add_command/add_path/absolute_path.c		\
	parser/simplify_tokens/add_command/add_path/add_path.c			\
	parser/simplify_tokens/add_command/add_path/builtin.c			\
	parser/simplify_tokens/add_command/add_path/command.c			\
\
	parser/simplify_tokens/add_command/add_args.c		\
	parser/simplify_tokens/add_command/add_command.c	\
	parser/simplify_tokens/add_command/get_files.c		\
\
	parser/simplify_tokens/get_subshells.c			\
	parser/simplify_tokens/simplify_tokens.c		\
\
	parser/syntax/is_syntax_ok.c	\
	parser/syntax/syntax_tools.c	\
\
	parser/parse_tokens.c	\
\
\
	exit_code.c			\
	get_cursor_x_pos.c	\
	get_here_docs.c		\
	main.c				\
	signal.c


DIR_INCS		=\
	include/			\
	$(LIBFT_INCLUDES)	\
	/opt/homebrew/opt/readline/include

INCLUDES		=	$(addprefix -I , $(DIR_INCS))

DIR_BUILD		=	.build/
OBJS			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEPS			=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
DEPS_FLAGS		=	-MMD -MP
CFLAGS			=	-Wall -Wextra -Werror -g3 -fsanitize=address -g3
RM				=	rm -rf
AR				=	ar rcs


LIBFT_PATH		=	lib/libft/
LIBFT_INCLUDES	=	$(LIBFT_PATH)include
LIBFT_L			=	-L$(LIBFT_PATH) -lft
LIBFT_L_DEBUG	=	-L$(LIBFT_PATH) -lft_debug
LIBFT_A			=	$(LIBFT_PATH)libft.a
LIBFT_A_DEBUG	=	$(LIBFT_PATH)libft_debug.a
MAKE_LIBFT		=	$(MAKE) -C $(LIBFT_PATH)

DEPENDENCIES	=	$(LIBFT_A)

.PHONY:		all
all:
			$(MAKE_LIBFT)
			$(MAKE) $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_L) -o $(NAME) -L/opt/homebrew/opt/readline/lib -lreadline


.PHONY:	clean
clean:
		$(MAKE_LIBFT) clean
		$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
		$(MAKE_LIBFT) fclean
		$(RM) $(NAME)

.PHONY:	re
re:		fclean
		$(MAKE) all

-include $(DEPS)

$(DIR_BUILD)%.o : $(SRC_PATH)%.c $(LIBFT_A)
		mkdir -p $(shell dirname $@)
		$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
