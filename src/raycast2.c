/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:46:38 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 02:00:35 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	perform_dda(t_raycast *rc, t_game *g);
void	calculate_wall_distance_and_draw_range(t_raycast *rc, t_game *g);
void	select_texture_and_calculate_tex_coords(t_raycast *rc, t_game *g);
void	draw_wall_column(t_raycast *rc, t_game *g, int x);

void	perform_dda(t_raycast *rc, t_game *g)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (g->map[rc->map_y][rc->map_x] != '0'
			&& g->map[rc->map_y][rc->map_x] != 'N'
			&& g->map[rc->map_y][rc->map_x] != 'S'
			&& g->map[rc->map_y][rc->map_x] != 'W'
			&& g->map[rc->map_y][rc->map_x] != 'E')
			rc->hit = 1;
	}
}

void	calculate_wall_distance_and_draw_range(t_raycast *rc, t_game *g)
{
	(void)g;
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	if (rc->perp_wall_dist < EPSILON)
		rc->perp_wall_dist = EPSILON;
	rc->line_height = (int)(HEIGHT / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + HEIGHT / 2;
	rc->out_screen = 0;
	if (rc->draw_start < 0)
	{
		rc->out_screen = -rc->draw_start;
		rc->draw_start = 0;
	}
	rc->draw_end = rc->line_height / 2 + HEIGHT / 2;
	if (rc->draw_end >= HEIGHT)
		rc->draw_end = HEIGHT - 1;
}

void	select_texture_and_calculate_tex_coords(t_raycast *rc, t_game *g)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir_x > 0)
			rc->texture = &g->we_texture;
		else
			rc->texture = &g->ea_texture;
	}
	else
	{
		if (rc->ray_dir_y > 0)
			rc->texture = &g->no_texture;
		else
		rc->texture = &g->so_texture;
	}
	if (rc->side == 0)
		rc->wall_x = g->player.y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = g->player.x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)rc->texture->width);
	if (rc->side == 0 && rc->ray_dir_x < 0)
		rc->tex_x = rc->texture->width - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y > 0)
		rc->tex_x = rc->texture->width - rc->tex_x - 1;
}

void	draw_wall_column(t_raycast *rc, t_game *g, int x)
{
	int		y;
	int		color;
	char	*src;
	char	*dst;
	int		bpp;

	y = rc->draw_start;
	bpp = g->img.bits_per_pixel / 8;
	while (y < rc->draw_end)
	{
		rc->tex_y = (int)(((y - rc->draw_start + rc->out_screen)
					* (double)rc->texture->height) / rc->line_height);
		src = rc->texture->img.addr + rc->tex_y * rc->texture->img.line_length
			+ rc->tex_x * (rc->texture->img.bits_per_pixel / 8);
		color = *(unsigned int *)src;
		dst = g->img.addr + y * g->img.line_length + x * bpp; 
		*(unsigned int *)dst = color;
		y++;
	}
}
