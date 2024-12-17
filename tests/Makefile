CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = ../libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRCS = ../src/main_utils.c \
      ../src/lexer/lexer.c \
	  ../src/lexer/lexer_utils.c \

TESTS = unit/test_lexer.c 

all: $(LIBFT_LIB) tests

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

tests: $(TESTS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRCS) $(TESTS) -o test_suite $(LIBFT_LIB)

run:
	./test_suite

clean:
	rm -f test_suite

