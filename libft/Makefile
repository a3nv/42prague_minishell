# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/22 22:56:57 by iasonov           #+#    #+#              #
#    Updated: 2025/01/05 18:25:12 by iasonov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= cc
CFLAGS	= -Wall -Wextra -Werror -g
AR		= ar rcs
NAME	= libft.a
HEADER	= libft.h

SRC	=	ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_isspace.c	\
		ft_itoa.c		\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_putchar_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_split_mult.c	\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_strndup.c		\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strlcat.c 	\
		ft_strlcpy.c	\
		ft_strlen.c 	\
		ft_strmapi.c	\
		ft_strncmp.c	\
		ft_strcmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_tolower.c	\
		ft_toupper.c	\
		ft_write_fd.c	\
		ft_str_builder.c	\
		ft_pair.c	\
		gnl/gnl.c 		\
		gnl/gnl_utils.c	\
		hashmap/ft_hashmap.c \
		hashmap/ft_hashmap_insert.c \
		hashmap/ft_hashmap_iteri.c \
		hashmap/ft_hashmap_utils.c \
		arraylist/ft_array_list_add.c \
		arraylist/ft_array_list_create.c \
		arraylist/ft_array_list_get.c \
		arraylist/ft_array_list_remove.c \

BONUS =	ft_lstadd_back_bonus.c	\
		ft_lstadd_front_bonus.c	\
		ft_lstclear_bonus.c		\
		ft_lstdelone_bonus.c	\
		ft_lstiter_bonus.c		\
		ft_lstlast_bonus.c		\
		ft_lstmap_bonus.c		\
		ft_lstnew_bonus.c		\
		ft_lstsize_bonus.c		\

BUILD_DIR = build
OBJ		= $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
BONUS_OBJS = $(addprefix $(BUILD_DIR)/, $(BONUS:.c=.o))

all: $(NAME)

$(BUILD_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJ) $(BONUS_OBJS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
