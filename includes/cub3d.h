/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:47:26 by nharraqi          #+#    #+#             */
/*   Updated: 2025/08/21 16:14:47 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../includes/minilibx-linux/mlx.h"
# include "../includes/minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../includes/libft/libft.h"
# include <X11/keysym.h>
# include <limits.h>
# include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1010
# define BLOCK 64
# define DEBUG 2
# define TRUE 1
# define FALSE 0  

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 0xff1b
# define QUIT 17

# define PI 3.14159265358979323846
# define PLAYER_RADIUS 0.2
# define EPSILON 0.01

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define GREY 0x808080
# define RED 0xFF0000
# define GREEN 0x00FF00
# define PURPLE 0xD8BFD8

typedef struct s_ig
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_ig;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		angle;
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			left_rotate;
	int			right_rotate;
}				t_player;

typedef struct s_texture
{
	t_ig		img;
	int			width;
	int			height;

}				t_texture;

/*==========================parsing 0==================================*/

typedef struct s_parser_context
{
	int			i;
	int			j;
	int			x;
	int			start_map;
	int			end_map;
	int			map_size;
}				t_parser_context;

typedef struct s_doc
{
	int			fd;
	char		**map;
	char		**new_map;
	char		*line;
	int			i;
	int			j;
	int			size;
}				t_doc;

/*==========================parsing 0==================================*/

typedef struct s_raycast
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			out_screen;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	t_texture	*texture;
}				t_raycast;

typedef struct s_movement
{
	double		move_speed;
	double		rot_speed;
	double		new_x;
	double		new_y;
	double		old_dir_x;
	double		old_plane_x;
}				t_movement;

typedef struct s_game
{
   void		*mlx;
   void		*win;
   t_ig	img;
   char		*addr;
   int		bits_per_pixel;
   int		line_length;
   int		endian;
   char		player_init_direction;
   
   int		start_map;
   char		**doc;
   char		**map;
   char		*north_texture;
   char		*south_texture;
   char		*west_texture;
   char		*east_texture;
   int		index_player[2];
   char		orientation_spawn;
   int		floor_color[3];
   int		ceiling_color[3];
   int		c_color;
   int		f_color;
   t_texture	no_texture;
   t_texture	so_texture;
   t_texture	we_texture;
   t_texture	ea_texture;
   
   t_player	player;

} t_game;

typedef struct s_spawn_ctx
{
	t_game		*dt;
	int			d_flag;
}				t_spawn_ctx;

//---------------doc_reader.c-------------------//
char **get_doc(const char *filename);
int	ensure_capacity(t_doc *ctx);
int ctx_init(t_doc *ctx, const char *filename);
char **allocate_map(int size);
char **reallocate_map(char **map, int pre_size, int new_size);

//---------------doc_reader2.c-------------------//
void process_line(t_doc *ctx);
void closing_fd(t_doc *ctx);

//---------------init_load_textures.c-------------------//
void	load_texture(t_game *g, t_texture *texture, char *path);
void	load_textures(t_game *g);
void	free_game(t_game *g);
void	free_textures_ulimit(t_game *g);
void	free_textures(t_game *g);

//---------------init_load_textures2.c-------------------//
void puterr(const char *s);
void tex_fail(t_game *g, const char *s);
void tex_load_img_or_die(t_game *g, t_texture *t, char *path);
void tex_get_addr_or_die(t_game *g, t_texture *t);


//---------------initcore.c-------------------//
void game_init(t_game *g, const char *s);
void player_zero(t_game *g);
void texture_path_zero(t_game *g);
void colors_zero(t_game *g);
void layout_load(t_game *g, const char *s);

//---------------initcore2.c-------------------//
void	init_player_pos(t_game *g);
void	init_mlx(t_game *g);
void	init_colors(t_game *g);
void	initialize_context(t_doc *ctx, const char *filename);

//---------------manage_close.c-------------------//
int	key_press(int keycode, t_game *g);
int	key_release(int keycode, t_game *g);
void	closing(t_game *g);
int	ft_close(t_game *g);

//---------------move_player.c-------------------//
void	init_movement(t_movement *m);
void	handle_forward_backward_movement(t_game *g, t_movement *m);
void	move_forward_backward(t_game *g, t_movement *m, int dir);
int		is_near_wall(t_game *g, double nx, double ny);
int		is_blocking(const t_game *g, int y, int x);

//---------------move_player2.c-------------------//
void	handle_left_right_movement(t_game *g, t_movement *m);
void	move_left_right(t_game *g, t_movement *m, int dir);
void	handle_rotation(t_game *g, t_movement *m);
void	rotate_player(t_game *g, t_movement *m, int dir);
void	put_pixel(t_ig *img, int x, int y, int color);

//---------------p_color.c-------------------//
void	handle_color_directive(t_game *g, t_parser_context *ctx, char *line);
int		parse_color_line(char *s);
void	 rgb_parse_triplet(char *s, int color[3], t_game *g);

//---------------p_color_utils.c-------------------//
long 	my_strtol(const char *str, char **endptr);
int		is_digit(int c);
void	free_wrong_color(t_game *g);
void	protect_wrong_color(char **ptr, t_game *g);

//---------------p_color_utils2.c-------------------//
int	get_digit_value(char c);
int	is_valid_digit(int digit, int base);

//---------------config_parse_utils.c-------------------//
int is_space(int c);
char tex_id_from_line(const char *line);
char **slot_by_id(t_game *g, char id);
char	*parse_doc_line(char *str);
void	handle_texture_directive(t_game *g, t_parser_context *ctx,
		char *line);

//---------------config_parse_utils2.c-------------------//
int is_map_char(int c);
int is_map_line(const char *str);
void	check_multiple_spawns(int *d_flag, t_game *dt);

//---------------config_parse.c-------------------//
void parsing_config(t_game *g, char **doc);
void parser_ctx_zero(t_parser_context *ctx);
void parse_identifiers(t_game *g, char **doc, t_parser_context *ctx);
void	check_identifiers(t_game *g, int count);
void	map_from_doc(t_game *g, char **doc, int start_map, int map_size);

//---------------config_parse2.c-------------------//
int	find_map_start(char **doc, int i);
int	found_end_map(char **doc);
int	tablen(char **tab);
int	calculate_map_size(char **doc, int start_map, int end_map);
int	no_empty_line(char **doc, int i, int is_map);

//---------------p_doc.c-------------------//
int	validate_identifier(char *line);
int	parse_doc(char **doc, int start_map);
void	exit_properly_parsing(t_game *g);

//---------------p_player.c-------------------//
void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	check_multiple_spawns(int *d_flag, t_game *dt);
void	player_spawn(char **map, t_game *dt);
int		map_char_kind(char c);

//---------------p_player2.c-------------------//
void	check_spawn_validity(char **map, int i, int j, t_game *dt);
int		neighbors_ok(char **map, int i, int j, int h);
void	last_check_spawn(char **map, int i, int *j, t_game *dt);
void	set_player_position(char **map, int i, int j, t_game *dt);
void	die_spawn(t_game *g, const char *msg);

//---------------p_textures.c-------------------//
void	assign_texture(t_game *g, t_parser_context *ctx, char c, char *doc);
char	**texture_slot(t_game *g, char id);

//---------------p_validate_utils.c-------------------//
bool	valid_texture(t_game *g);
bool	has_xpm_suffix(const char *path);
int	check_texture_path(const char *path);
double	safe_delta(double ray);

//---------------p_wall.c-------------------//
char **parse_wall(char **map, t_game *g);
int	found_max_width(char **map);
char	**check_top_border(char **map);
char	**check_bottom_border(char **map, int map_height);
void	die_wall(t_game *g, const char *msg);

//---------------p_wall2.c-------------------//
char	**check_first_border(char **map);
void	check_null_line(char *line);
int	right_border_ok(char *line);
int	zero_surround_ok(char **map, int i, int j, int map_height);
char	**check_inner_lines(char **map, int map_height);

//---------------p_wall3.c-------------------//
int	ft_strlen_skip_empty_line(char *map);
void	free_game_wall(t_game *g);
char	**check_first_char(char **map, int map_height);

//---------------p_wall4.c-------------------//
int	is_valid_tile(char c);
int	check_up_tile(char **map, int r, int c);
int	check_down_tile(char **map, int r, int c, int map_height);
char	**check_map_validity(char **map, int map_height, int max_width);

//---------------p_wall5.c-------------------//
int	is_above_cell_valid(char **map, int r, int c);
int	is_below_cell_valid(char **map, int r, int c, int map_height);
int	is_cell_valid(char **map, int r, int c, int map_height);
char	**check_map(char **map, int map_height, int max_width);

//---------------parsing1.c-------------------//
int	parse_av(char *filename);
void verif_name(char *s);
char *extracting_extension(char *s);
int verif_extension(char *ext);

//---------------raycast.c-------------------//
void	raycast(t_game *g);
void	init_raycast(t_raycast *rc, t_game *g, int x);
void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *g);
void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *g);
void	calculate_step_and_side_dist(t_raycast *rc, t_game *g);

//---------------raycast2.c-------------------//
void	perform_dda(t_raycast *rc, t_game *g);
void	calculate_wall_distance_and_draw_range(t_raycast *rc, t_game *g);
void	select_texture_and_calculate_tex_coords(t_raycast *rc, t_game *g);
void	draw_wall_column(t_raycast *rc, t_game *g, int x);

//---------------drawing.c-------------------//
void	move_player(t_game *g);
void	draw_floor_and_ceiling(t_game *g);
int		drawing(t_game *g);

//---------------verify_info.c-------------------//
void verify_info(t_game *g);
void free_game_texture(t_game *g, char *txt);
void	free_tab(char **tab);

//---------------verify_info_utils.c-------------------//
size_t s_len(const char *s);
int id_code(const char *s);
void scan_identifiers(t_game *g, int seen[6]);

#endif