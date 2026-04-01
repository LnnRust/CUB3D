# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 14:11:11 by aandreo           #+#    #+#              #
#    Updated: 2026/03/31 18:01:20 by aandreo          ###   ########.fr        #
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

GNL_SRCS	= libft/get_next_line.c \
			  libft/get_next_line_utils.c

OBJS_DIR	= objs
OBJS		= $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)
GNL_OBJS	= $(GNL_SRCS:libft/%.c=$(OBJS_DIR)/libft/%.o)

# ──────────────────────────── Rules ────────────────────────────── #

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

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
