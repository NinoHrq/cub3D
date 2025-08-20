# this is to manage flags for m1 architecture, we don't have to use this flag in linux
OS_ARCH 	:= $(shell uname -m)
ifeq ($(OS_ARCH),arm64)
MLX_DIR := ./includes/minilibx_macos/
MLX_LIB := -lmlx -framework OpenGL -framework AppKit
else
MLX_DIR := ./includes/minilibx-linux/
MLX_LIB := -lmlx -lXext -lX11
endif

# Executable name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
INC_DIR = ./includes
SRC_DIR = ./src
OBJ_DIR = ./obj

# Source files
SRCS =  doc_reader.c \
doc_reader2.c \
init_load_textures.c \
initcore.c \
initcore2.c \
main.c \
manage_close.c \
move_player.c \
move_player2.c \
p_color.c \
p_colors_utils.c \ 
p_colors_utils2.c \
config_parse_utils.c \
config_parse.c \
config_parse2.c \
p_doc.c \
p_player.c \
p_player2.c \
p_textures.c \
p_validate_utils.c \
p_wall.c \
p_wall2.c \
p_wall3.c \
p_wall4.c \
p_wall5.c \
parsing1.c \
raycast.c \
raycast2.c \
redraw.c \
verify_info.c \
verify_info_utils.c \
config_parse_utils2.c

# Object files
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Includes directories
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Default rule
all: $(NAME)

# Create the cub3D program
$(NAME): $(OBJS) $(LIBFT) $(MLX)
@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L$(MLX_DIR) $(MLX_LIB) -lm -o $(NAME)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Ensure the object directory exists
$(OBJ_DIR):
@mkdir -p $(OBJ_DIR)

# Build the library (libft)
$(LIBFT):
@$(MAKE) -C $(LIBFT_DIR)

# Build the minilibx library
$(MLX):
@$(MAKE) -s -C $(MLX_DIR)

# Clean object files
clean:
rm -rf $(OBJ_DIR)

# Clean object files and executable
fclean: clean
rm -f $(NAME)
@$(MAKE) -C $(LIBFT_DIR) fclean
@$(MAKE) -s -C $(MLX_DIR) clean

# Rebuild the library and the main program
re: fclean all

# Phony targets
.PHONY: all clean fclean re
