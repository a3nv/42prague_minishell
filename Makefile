NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Ilibft

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
	  src/executor/executor.c

OBJECTS = $(SRC:.c=.o)

all: $(LIBFT_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_LIB)

$(OBJECTS): includes/minishell.h

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test:
	make -C test

run_test:
	make -C test run

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_PATH)
	make clean -C test

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

norm: 
	norminette $(SRC) includes/minishell.h $(LIBFT_PATH)*.h $(LIBFT_PATH)*.c

.PHONY: all fclean clean re norm test run_tes
