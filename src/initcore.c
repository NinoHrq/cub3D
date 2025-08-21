/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initcore.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:19:27 by nharraqi          #+#    #+#             */
/*   Updated: 2025/07/17 00:41:10 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void game_init(t_game *g, const char *s);
void player_zero(t_game *g);
void texture_path_zero(t_game *g);
void colors_zero(t_game *g);
void layout_load(t_game *g, const char *s);

void game_init(t_game *g, const char *path)
{
	g->no_texture.img.img = NULL;
	g->so_texture.img.img = NULL;
	g->we_texture.img.img = NULL;
	g->ea_texture.img.img = NULL;
	g->img.img = NULL;
	g->mlx = NULL;
	g->win = NULL;
    player_zero(g);
	texture_path_zero(g);
	colors_zero(g);
	layout_load(g, path);
	init_player_pos(g);
	init_mlx(g);
	init_colors(g);
	load_textures(g);	
}

void player_zero(t_game *g)
{
	g->player.key_up = 0;
	g->player.key_down = 0;
	g->player.key_left = 0;
	g->player.key_right = 0;
	g->player.left_rotate = 0;
	g->player.right_rotate = 0;
}

void texture_path_zero(t_game *g)
{
	g->north_texture = NULL;
	g->west_texture = NULL;
	g->east_texture = NULL;
	g->south_texture = NULL;
}

void colors_zero(t_game *g)
{
	g->floor_color[0] = -1;
	g->floor_color[1] = -1;
	g->floor_color[2] = -1;
	g->ceiling_color[0] = -1;
	g->ceiling_color[1] = -1;
	g->ceiling_color[2] = -1;
}

void layout_load(t_game *g, const char *path)
{
	g->start_map = 0;
	g->doc = get_doc(path);
	if(!g->doc)
		exit(1);
	verify_info(g);
	parsing_config(g, g->doc);
	if (parse_doc(g->doc, g->start_map))
		exit_properly_parsing(g);
	if (g->floor_color[0] == -1 || g->floor_color[1] == -1
		|| g->floor_color[2] == -1 || g->ceiling_color[0] == -1
		|| g->ceiling_color[1] == -1 || g->ceiling_color[2] == -1)
	{
		free_tab(g->doc);
		free_tab(g->map);
		g->map = NULL;
	}
	if (g->map)
		g->map = parse_wall(g->map, g);
	if (g->map)
		player_spawn(g->map, g);
	else
		free_game_texture(g, "");	
}
