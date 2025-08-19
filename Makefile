# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 21:43:31 by zslowian          #+#    #+#              #
#    Updated: 2025/08/19 16:19:42 by zslowian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lX11 -lXext
LIBFT_FLAGS = -lft
MATH_FLAGS = -lm
RM = rm -rf

MLX_DIR = minilibx-linux
LIBFT_DIR = libft

SRC = main.c \
	clean.c \
	debug.c \
	error.c \
	init.c \
	map.c \
	color_utils.c \
	parse.c \
	tokenize.c \
	validate_utils.c \
	validate.c \
	check_horizontal.c \
	check_vertical.c \
	game_loop.c \
	init_window.c \
	ray_angles.c \
	cast_rays.c \
	hooks.c \
	textures.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) \
	-L$(MLX_DIR) $(MLX_FLAGS) \
	-L$(LIBFT_DIR) $(LIBFT_FLAGS) \
	-no-pie \
	$(MATH_FLAGS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(MLX_DIR)/libmlx.a

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all
