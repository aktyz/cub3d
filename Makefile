# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 21:43:31 by zslowian          #+#    #+#              #
#    Updated: 2025/08/12 10:21:40 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -lmlx -lX11 -lXext
LIBFT_FLAGS = -lft
MATH_FLAGS = -lm
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
	parse_utils.c \
	parse.c \
	tokenize.c \
	validate.c \
	check_horizontal.c \
	check_vertical.c \
	game_loop.c \
	init_window.c \
	ray_angles.c \
	cast_rays.c \
	hooks.c
	

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) \
	-L $(MLX) $(MLX_FLAGS) \
	-L $(LIBFT) $(LIBFT_FLAGS) \
	-no-pie \
	$(MATH_FLAGS)

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
	-no-pie -g \
	$(MATH_FLAGS)

re: fclean all
