NAME = minishell
DEBUG_NAME = minishell_debug

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft
DEBUG_FLAGS = -DDEBUG_MODE=1
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRC = src/main.c \
	  src/main_utils.c \
	  src/printer/tree_printer.c \
	  src/lexer/lexer.c \
	  src/lexer/lexer_utils.c \
	  src/parser/parser.c \
	  src/parser/parser_node_utils.c \
	  src/parser/parser_utils.c \
	  src/executor/executor.c \
	  src/executor/builtin_pwd.c

OBJECTS = $(SRC:.c=.o)
DEBUG_OBJECTS = $(SRC:.c=_debug.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

%_debug.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB)

debug: $(LIBFT_LIB) $(DEBUG_OBJECTS)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $(DEBUG_NAME) $(DEBUG_OBJECTS) $(LIBFT_LIB)

$(OBJECTS): includes/minishell.h

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test:
	make -C test

run_test:
	make -C test run

clean:
	rm -f $(OBJECTS) $(DEBUG_OBJECTS)
	make clean -C $(LIBFT_PATH)
	make clean -C test

fclean: clean
	rm -f $(NAME) $(DEBUG_NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all


norm:
	norminette $(SRC) includes/minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c $(LIBFT_PATH)gnl/*.c $(LIBFT_PATH)hashmap/*.c

.PHONY: all fclean clean re norm test run_tes
