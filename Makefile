NAME		= minishell
CC			= cc
CFLAGS		= -Wextra -Wall -Werror
LDFLAGS		= -lreadline

LIBFT_DIR 	= ./lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj/
SRC_DIR		= src/

INCLUDES	= -I ./inc -I $(LIBFT_DIR)/inc

LIBFTH		= $(LIBFT_DIR)/inc/libft.h
HEADERS		=	inc/minishell.h \
				inc/ast.h \
				inc/builtin.h \
				inc/environment.h \
				inc/error.h \
				inc/execution.h \
				inc/expansion.h \
				inc/heredoc.h \
				inc/lexing.h \
				inc/memory_arena.h \
				inc/quotes_handler.h \
				inc/signals.h

SRC			=	main.c \
				minishell.c \
				0.error_handling/error.c \
				0.init-delete/init_minishell.c \
				0.init-delete/delete_minishell.c \
				0.init-delete/shell_level.c  \
				0.global_utils/utils.c \
				0.memory_arena/memory_arena.c \
				0.memory_arena_libft/ft_arena_calloc.c \
				0.memory_arena_libft/ft_arena_strdup.c \
				0.memory_arena_libft/ft_arena_strjoin.c \
				0.signals/signals.c \
				0.signals/signals_handlers.c \
				1.environment/environment.c \
				1.environment/free_env.c \
				2.input_validation/input_validation.c \
				3.tokens/create_tokens.c \
				3.tokens/init_lexer.c \
				3.tokens/retokenize_words_utils.c \
				3.tokens/retokenize_words.c \
				3.tokens/tokenizer_utils.c \
				3.tokens/tokenizer.c \
				3.tokens/tokens_validation.c \
				4.heredoc/heredoc.c \
				4.heredoc/heredoc_utils.c \
				4.heredoc/heredoc_tmp_files.c \
				4.heredoc/heredoc_cleanup.c \
				5.quotes_handle/quotes_handler.c \
				5.quotes_handle/quotes_handler_init.c \
				5.quotes_handle/quotes_handler_utils.c \
				5.quotes_handle/quotes_handler_utils2.c \
				6.expansion/expansion.c \
				6.expansion/expansion_utils.c \
				7.ast/ast.c \
				7.ast/ast_branch_building.c \
				7.ast/ast_utils.c \
				7.ast/ast_create_node.c \
				8.redirection/open.c \
				8.redirection/dup2.c \
				8.redirection/redir.c \
				9.execution/execute_builtin.c \
				9.execution/execution.c \
				9.execution/child_process.c \
				9.execution/path.c \
				9.execution/setup.c \
				9.execution/wait.c \
				10.builtins/ft_env.c \
				10.builtins/ft_pwd.c \
				10.builtins/ft_cwd.c \
				10.builtins/ft_cd.c \
				10.builtins/ft_echo.c \
				10.builtins/ft_exit.c \
				10.builtins/ft_unset.c \
				10.builtins/ft_export.c \
				10.builtins/utils_builtins.c \
				10.builtins/ft_export_sort_env.c

OBJS		= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) $(LIBFTH)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(LIBFT) $(OBJS) $(HEADERS) $(LIBFTH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "\033[0;32mMinishell built successfully ✅\033[0m"


clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "\033[0;32mMinishell cleaned successfully ✅\033[0m"


fclean: clean
	@rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re
