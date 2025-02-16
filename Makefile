NAME = bin/minishell
DEBUG_NAME = bin/minishell_debug

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft
LDFLAGS = -lreadline
DEBUG_FLAGS = -DDEBUG_MODE=1
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

ifeq ($(shell uname -s), Darwin)
	READLINE_PREFIX := $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_PREFIX)/include
	LDFLAGS := -L$(READLINE_PREFIX)/lib $(LDFLAGS)
endif

SRC = src/main.c \
	  src/utils/alloc_utils.c \
	  src/utils/main_utils.c \
	  src/utils/binary_utils.c \
	  src/utils/env_utils.c \
	  src/utils/executor_utils.c \
	  src/gc/gc.c \
	  src/printer/tree_printer.c \
	  src/printer/main_printer.c \
	  src/lexer/lexer.c \
	  src/lexer/lexer_utils.c \
	  src/parser/parser.c \
	  src/parser/parser_node_utils.c \
	  src/parser/parser_utils.c \
	  src/parser/env_expander.c \
	  src/executor/executor.c \
	  src/executor/builtin_pwd.c \
	  src/executor/builtin_cd.c \
	  src/executor/builtin_exit.c \
	  src/executor/builtin_echo.c \
	  src/executor/builtin_env.c \
	  src/executor/builtin_export.c \
	  src/executor/builtin_unset.c \
	  src/executor/pipe.c \
	  src/executor/binary.c \
	  src/executor/binary_helper.c \
	  src/executor/heredoc_utils.c \
	  src/executor/redirection_utils.c \
	  src/signal/signal.c \
	  src/validator/validator.c \
	  src/validator/validator_list.c \
	  src/validator/validator_list_utils.c \

BUILD_DIR = build
BIN_DIR = bin
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEBUG_OBJECTS = $(addprefix $(BUILD_DIR)/, $(SRC:.c=_debug.o))

all: $(LIBFT_LIB) $(NAME)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%_debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB) $(LDFLAGS)

debug: $(LIBFT_LIB) $(DEBUG_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_NAME) $(DEBUG_OBJECTS) $(LIBFT_LIB) $(LDFLAGS)

$(OBJECTS): includes/minishell.h

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test:
	make -C test

test_run:
	make -C test run

clean:
	rm -rf $(BUILD_DIR)
	make clean -C $(LIBFT_PATH)
	make clean -C test

fclean: clean
	rm -rf $(BIN_DIR)
	make fclean -C $(LIBFT_PATH)

re: fclean all


norm:
	norminette $(SRC) includes/minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c $(LIBFT_PATH)gnl/*.c $(LIBFT_PATH)hashmap/*.c

.PHONY: all fclean clean re norm test test_run
