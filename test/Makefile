CC = cc
CFLAGS = -Wall -Wextra -Werror -g --coverage
LDFLAG = --coverage

LIBFT_PATH = ../libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

SRCS = ../src/utils/main_utils.c \
      ../src/gc/gc.c \
      ../src/lexer/lexer.c \
	  ../src/lexer/lexer_utils.c \

TESTS = unit/test_lexer.c 

all: $(LIBFT_LIB) test

$(LIBFT_LIB):
	make bonus -C $(LIBFT_PATH)

test: $(TESTS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRCS) $(TESTS) -o test_suite $(LIBFT_LIB) $(LDFLAG)

run:
	./test_suite

clean:
	rm -f test_suite

