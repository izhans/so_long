# Variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

VPATH = src/:src/map/:

SRC	=	map_utils.c \
		so_long.c \

OBJ_DIR = objects
OBJ =	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

MLX_DIR = mlx_linux

MLX	=	$(MLX_DIR)/libmlx_Linux.a
LIBFT = libft/libft.a

MLX_OBJ =	-I/usr/include -Imlx_linux -O3
MLX_LINK =	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LINK) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(MLX_OBJ) -c $< -o $@

clean:
	make -C $(dir $(LIBFT)) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(dir $(LIBFT)) fclean
	rm -f $(NAME)

re: fclean all