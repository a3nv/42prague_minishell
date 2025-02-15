CC = cc
CFLAGS = -Wall -Wextra -Werror -g --coverage -I../includes
#CFLAGS = -Wall -Wextra -Werror -g --coverage -I/usr/local/include -I../includes
LDFLAG = --coverage -lcriterion

BUILD_DIR = build
BIN_DIR = bin
OUTPUT = $(BIN_DIR)/test_suite

LIBFT_PATH = ../libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRCS = ../src/utils/main_utils.c \
	   ../src/utils/executor_utils.c \
	   ../src/utils/binary_utils.c \
	   ../src/utils/env_utils.c \
       ../src/gc/gc.c \
       ../src/parser/parser.c \
       ../src/parser/parser_utils.c \
       ../src/parser/parser_node_utils.c \
       ../src/parser/env_expander.c \
       ../src/lexer/lexer.c \
	   ../src/lexer/lexer_utils.c \
	   ../src/executor/binary.c \
	   ../libft/arraylist/ft_array_list_add.c \
	   ../libft/arraylist/ft_array_list_create.c \
	   ../libft/arraylist/ft_array_list_get.c \
	   ../libft/arraylist/ft_array_list_remove.c \

TESTS = \
		unit/test_binary.c \
		unit/test_lexer.c \
		unit/test_executor_utils.c \
		unit/test_array_list.c \

# unit/test_envp_utils.c \

all: $(LIBFT_LIB) test

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test: $(TESTS) $(LIBFT_LIB)
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(TESTS) -o $(OUTPUT) $(LIBFT_LIB) $(LDFLAG)

run: test
	$(OUTPUT) --verbose
#	$(OUTPUT) 

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

coverage: test
	$(OUTPUT)
	gcovr --exclude-unreachable-branches --exclude-throw-branches --html --html-details -o coverage.html

.PHONY: all clean run coverage
