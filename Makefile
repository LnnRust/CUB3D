# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 14:11:11 by aandreo           #+#    #+#              #
#    Updated: 2026/04/22 20:39:42 by fbenech          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I headers -I libft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

LDFLAGS		= -L$(LIBFT_DIR) -lft

# ──────────────────────────── Sources ──────────────────────────── #

SRCS		= srcs/main.c \
			  srcs/parsing/read_file.c \
			  srcs/parsing/parse_getters.c \
			  srcs/parsing/flood_fill.c \
			  srcs/parsing/parse_utils.c \
			  srcs/exec/main.c \
			  srcs/exec/pixels.c \
			  srcs/exec/utils.c \
			  srcs/exec/raycasting.c \


GNL_SRCS	= libft/get_next_line.c \
			  libft/get_next_line_utils.c

OBJS_DIR	= objs
OBJS		= $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)
GNL_OBJS	= $(GNL_SRCS:libft/%.c=$(OBJS_DIR)/libft/%.o)

MLX_DIR		= MLX42
MLX_LIB		= $(MLX_DIR)/build/libmlx42.a
MLX_INC		= -I$(MLX_DIR)/include
MLX_LNK		= -L$(MLX_DIR)/build -lmlx42 -lglfw -ldl -lpthread -lm

# ──────────────────────────── Rules ────────────────────────────── #

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(MLX_LIB):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build -DDEBUG=0
	cmake --build $(MLX_DIR)/build -j4

$(NAME): $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LDFLAGS) $(MLX_LNK) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INC) -c $< -o $@

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
