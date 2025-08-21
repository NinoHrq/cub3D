# ========= Makefile minimal, sans TAB =========
.RECIPEPREFIX := >
NAME    := cub3D
CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INC_DIR := ./includes
SRC_DIR := ./src
OBJ_DIR := ./obj
LIBFT_DIR := $(INC_DIR)/libft
LIBFT     := $(LIBFT_DIR)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  MLX_DIR  := $(INC_DIR)/minilibx_macos
  MLX_LIBS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
  MLX_DIR  := $(INC_DIR)/minilibx-linux
  MLX_LIBS := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
endif
INCS := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean fclean re libft mlx

all: $(NAME)

$(NAME): libft mlx $(OBJS)
> $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
> $(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
> mkdir -p $(OBJ_DIR)

libft:
> $(MAKE) -C $(LIBFT_DIR)

mlx:
> $(MAKE) -C $(MLX_DIR)

clean:
> rm -rf $(OBJ_DIR)
> $(MAKE) -C $(LIBFT_DIR) clean
> $(MAKE) -C $(MLX_DIR) clean

fclean: clean
> rm -f $(NAME)
> $(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(OBJS:.o=.d)
