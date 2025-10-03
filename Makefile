NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline
RM = rm -f
INCLUDES = -I./includes/ -I./libft/includes/

SRCS = main.c \
	./tokenizing/tokenizing.c ./tokenizing/clean_tokens.c \
	./tokenizing/tokenizing_utils.c ./tokenizing/handle_pipe_redir.c \
	./tokenizing/handle_quotes.c ./tokenizing/handle_variable.c \
	./tokenizing/handle_word.c \
	./parsing/parsing.c ./parsing/add_arg.c \
	./parsing/add_redir.c ./parsing/clean_ast.c ./parsing/create_node.c \
	./parsing/parse_command.c ./exec/exec_builtin_utils.c \
	./parsing/parse_expression.c ./parsing/parse_redirection.c \
	./signals/setup_signals.c ./heredoc/handle_heredoc.c \
	./heredoc/heredoc_util.c \
	./env/env_util.c ./env/envp_to_array.c ./env/init_envp.c \
	./exec/exec.c ./exec/exec_builtin.c ./exec/built_ins/builtin_pwd.c \
	./exec/built_ins/builtin_export.c ./exec/built_ins/builtin_utils.c \
	./exec/built_ins/builtin_exit.c ./exec/built_ins/builtin_env.c \
	./exec/built_ins/builtin_unset.c ./heredoc/exp_heredoc.c \
	./exec/exec_pipe.c ./exec/non_builtin/exec_non_builtin.c \
	./exec//non_builtin/exec_util_access.c ./exec//non_builtin/exec_util_clean.c \
	./exec//non_builtin/exec_util_file.c ./exec//non_builtin/exec_util_path.c \
	./exec/built_ins/builtin_export_utils.c ./exec/built_ins/builtin_cd.c\
	./exec/built_ins/builtin_echo.c

OBJ_DIR = ./obj

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline_suppress.supp ./$(NAME)

valchild: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline_suppress.supp ./$(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tokenizing $(OBJ_DIR)/parsing $(OBJ_DIR)/expanding \
	$(OBJ_DIR)/signals $(OBJ_DIR)/exec $(OBJ_DIR)/exec/built_ins \
	$(OBJ_DIR)/env $(OBJ_DIR)/exec/expansion $(OBJ_DIR)/heredoc \
	$(OBJ_DIR)/exec/non_builtin \

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
