# Variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

VPATH = src/:src/map/:

SRC	=	map_utils.c \
		so_long.c \

OBJ_DIR = objects
OBJ =	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

MLX	=	minilibx-linux/libmlx_Linux.a
LIBFT = libft/libft.a

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C minilibx-linux

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(dir $(LIBFT)) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(dir $(LIBFT)) fclean
	rm -f $(NAME)

re: fclean all