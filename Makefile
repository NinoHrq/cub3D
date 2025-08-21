# ========= Makefile portable (Linux/macOS) — sans TAB =========
.RECIPEPREFIX := >
NAME      := cub3D
CC        := cc
CFLAGS    := -Wall -Wextra -Werror
INC_DIR   := ./includes
SRC_DIR   := ./src
OBJ_DIR   := ./obj

# --- libft ---
LIBFT_DIR := $(INC_DIR)/libft
LIBFT     := $(LIBFT_DIR)/libft.a

# --- OS / MLX ---
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  MLX_DIR   := $(INC_DIR)/minilibx_macos
  MLX_LIBS  := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
  MLX_A     := $(MLX_DIR)/libmlx.a
else
  MLX_DIR   := $(INC_DIR)/minilibx-linux
  MLX_LIBS  := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
  # Le nom de la lib générée par minilibx-linux est libmlx.a
  MLX_A     := $(MLX_DIR)/libmlx.a
endif

INCS := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# --- sources/obj ---
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean fclean re libft mlx

# --- build final ---
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_A) $(OBJS)
> $(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIBS) -o $@

# --- objects ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
> $(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
> mkdir -p $(OBJ_DIR)

# --- libft ---
$(LIBFT):
> $(MAKE) -C $(LIBFT_DIR)

# --- mlx : construire UNIQUEMENT la librairie, pas la cible 'all' ---
# 1) Sur Linux, certains systèmes sont montés en 'noexec' -> on lance 'configure' via /bin/sh SI présent.
# 2) On construit la lib directement: 'make libmlx.a' (évite les tests et le re-appel de ./configure).
$(MLX_A):
> cd $(MLX_DIR) && { [ -f ./configure ] && /bin/sh ./configure || true; }
> $(MAKE) -C $(MLX_DIR) libmlx.a

# Raccourcis explicites
libft: $(LIBFT)
mlx:   $(MLX_A)

# --- clean ---
clean:
> rm -rf $(OBJ_DIR)
> -$(MAKE) -C $(LIBFT_DIR) clean
> -$(MAKE) -C $(MLX_DIR) clean

fclean: clean
> rm -f $(NAME)
> -$(MAKE) -C $(LIBFT_DIR) fclean
# Pas de fclean MLX : la lib se régénère au besoin.

re: fclean all

# --- deps auto ---
-include $(OBJS:.o=.d)
