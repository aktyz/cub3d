# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 21:43:31 by zslowian          #+#    #+#              #
#    Updated: 2025/08/21 13:16:56 by zslowian         ###   ########.fr        #
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
MLX = libmlx.a
LIBFT_DIR = libft

SRC = main.c \
	clean.c \
	debug.c \
	draw_frame.c \
	error.c \
	init.c \
	map.c \
	color_utils.c \
	parse.c \
	parse_utils.c \
	tokenize.c \
	tokenize_utils.c \
	validate_utils.c \
	validate.c \
	check_horizontal.c \
	check_ray_direction.c \
	check_vertical.c \
	game_loop.c \
	init_window.c \
	ray_angles.c \
	cast_rays_utils.c \
	cast_rays.c \
	hooks.c \
	hooks_move.c \
	hooks_utils.c \
	textures.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(LIBFT_DIR)/libft.a $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) \
	-L$(MLX_DIR) $(MLX_FLAGS) \
	-L$(LIBFT_DIR) $(LIBFT_FLAGS) \
	-no-pie \
	$(MATH_FLAGS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	git submodule update --init --recursive
	cd $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)
	cd ..

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

debug: $(OBJ)
	$(RM) $(NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) \
	-L$(MLX_DIR) $(MLX_FLAGS) \
	-L$(LIBFT_DIR) $(LIBFT_FLAGS) \
	-no-pie -g \
	$(MATH_FLAGS)

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./${NAME} ./resources/maps/subject.cub

re: fclean all
