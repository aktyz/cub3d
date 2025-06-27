# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 21:43:31 by zslowian          #+#    #+#              #
#    Updated: 2025/06/20 11:04:10 by zslowian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lX11 -lXext
LIBFT_FLAGS = -lft
MLX = minilibx-linux
MLX_SRC = git@github.com:42paris/minilibx-linux.git
LIBFT = libft
LIBFT_SRC = git@github.com:aktyz/libft.git
RM = rm -rf

SRC = main.c \
	clean.c \
	debug.c \
	error.c \
	init.c \
	map.c \
	parse.c \
	tokenize.c \
	validate.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) \
	-L $(MLX) $(MLX_FLAGS) \
	-L $(LIBFT) $(LIBFT_FLAGS) \
	-no-pie

$(MLX):
	@git clone $(MLX_SRC)
	@$(MAKE) -C ./minilibx-linux

$(LIBFT):
	@git clone $(LIBFT_SRC)
	@$(MAKE) -C ./libft

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) ./$(LIBFT)
	$(RM) ./$(MLX)

debug:
	$(RM) $(NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) \
	-L $(MLX) $(MLX_FLAGS) \
	-L $(LIBFT) $(LIBFT_FLAGS) \
	-no-pie -g

re: fclean all
