# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 16:24:47 by zslowian          #+#    #+#              #
#    Updated: 2025/04/27 16:16:15 by zslowian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR_SRC = src
DIR_OBJ = obj

SUBDIR = ft_printf gnl is lst main math mem put str str_arr to

SRC_DIR = $(foreach dir, $(SUBDIR), $(addprefix $(DIR_SRC)/, $(dir)))
#SRC_DIR = ./src/is ./src/lst ./src/mem ./src/put ./src/str ./src/to
OBJ_DIR = $(foreach dir, $(SUBDIR), $(addprefix $(DIR_OBJ)/, $(dir)))
#OBJ_DIR = ./obj/is ./obj/lst ./obj/mem ./obj/put ./obj/str ./obj/to
SRC = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
#SRC = ./src/is/ft_isalnum.c ... ./src/to/ft_toupper.c
OBJ = $(subst $(DIR_SRC), $(DIR_OBJ), $(SRC:.c=.o))

INCLUDES = -I headers

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_OBJ) $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -g

$(NAME): $(OBJ)
	@ar cr $(NAME) $(OBJ)
	@ranlib $(NAME)

all: $(NAME)

fclean: clean
	@rm -f $(NAME)
	@rm -fr $(DIR_OBJ)

clean:
	@rm -fr $(DIR_OBJ)

re: fclean all

.PHONY: all clean fclean re
