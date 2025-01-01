CC = cc
CFLAGS = -Wall -Wextra -Werror -g --coverage -I../includes
#CFLAGS = -Wall -Wextra -Werror -g --coverage -I/usr/local/include -I../includes
LDFLAG = --coverage -lcriterion

BUILD_DIR = build
OUTPUT = $(BUILD_DIR)/test_suite

LIBFT_PATH = ../libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRCS = ../src/utils/main_utils.c \
      ../src/gc/gc.c \
      ../src/lexer/lexer.c \
	  ../src/lexer/lexer_utils.c \

TESTS = unit/test_lexer.c \

all: $(LIBFT_LIB) test

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test: $(TESTS) $(LIBFT_LIB)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) $(TESTS) -o $(OUTPUT) $(LIBFT_LIB) $(LDFLAG)

run: test
	$(OUTPUT) --verbose

clean:
	rm -rf $(BUILD_DIR)

coverage: test
	$(OUTPUT)
	gcovr --exclude-unreachable-branches --exclude-throw-branches --html --html-details -o coverage.html

.PHONY: all clean run coverage
