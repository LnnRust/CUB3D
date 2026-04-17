# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 14:11:11 by aandreo           #+#    #+#              #
#    Updated: 2026/04/16 19:05:51 by aandreo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I headers -I libft -I MLX42/include

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= MLX42
MLX_BUILD_DIR	= $(MLX_DIR)/build
MLX			= $(MLX_BUILD_DIR)/libmlx42.a

LDFLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_BUILD_DIR) -lmlx42 -ldl -lglfw -pthread -lm

# ──────────────────────────── Sources ──────────────────────────── #

SRCS		= srcs/main.c \
			  srcs/parsing/read_file.c \
			  srcs/parsing/flood_fill.c \
			  srcs/parsing/config/parse_config.c \
			  srcs/parsing/config/utils2.c \
			  srcs/parsing/utils/utils.c \
			  srcs/parsing/utils/utils2.c \
			  srcs/parsing/utils/setters.c \
			  srcs/parsing/parsing.c \

GNL_SRCS	= libft/get_next_line.c \
			  libft/get_next_line_utils.c

OBJS_DIR	= objs
OBJS		= $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)
GNL_OBJS	= $(GNL_SRCS:libft/%.c=$(OBJS_DIR)/libft/%.o)

# ──────────────────────────── Rules ────────────────────────────── #

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	cmake -S $(MLX_DIR) -B $(MLX_BUILD_DIR)
	cmake --build $(MLX_BUILD_DIR) -j4

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/libft/%.o: libft/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
