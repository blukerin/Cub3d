NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
LIBFT_DIR = libft
BONUS_DIR = bonus

MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
INCLUDES = -I. -I$(MLX_DIR) -I$(LIBFT_DIR)

SRC = main.c
OBJ = $(SRC:.c=.o)

BONUS_SRC = $(BONUS_DIR)/main_bonus.c\
			$(BONUS_DIR)/render_bonus.c \
			$(BONUS_DIR)/events_bonus.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -lm -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS) -lm -o $(BONUS_NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re