/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:40:18 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 01:25:02 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	raycast(t_game *g);
void	init_raycast(t_raycast *rc, t_game *g, int x);
void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *g);
void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *g);
void	calculate_step_and_side_dist(t_raycast *rc, t_game *g);

void	raycast(t_game *g)
{
	int			x;
	t_raycast	rc;

	x = 0;
	while (x < WIDTH)
	{
		init_raycast(&rc, g, x);
		calculate_step_and_side_dist(&rc, g);
		perform_dda(&rc, g);
		calculate_wall_distance_and_draw_range(&rc, g);
		select_texture_and_calculate_tex_coords(&rc, g);
		draw_wall_column(&rc, g, x);
		x++;
	}
}

void	init_raycast(t_raycast *rc, t_game *g, int x)
{
	ft_bzero(rc, sizeof(*rc));
	rc->camera_x = 2.0 * x / (double)WIDTH - 1.0;
	rc->ray_dir_x = g->player.dir_x + g->player.plane_x * rc->camera_x;
	rc->ray_dir_y = g->player.dir_y + g->player.plane_y * rc->camera_x;
	rc->map_x = (int)g->player.x;
	rc->map_y = (int)g->player.y;
	rc->delta_dist_x = safe_delta(rc->ray_dir_x);
	rc->delta_dist_y = safe_delta(rc->ray_dir_y);
}
void	calculate_x_step_and_side_dist(t_raycast *rc, t_game *g)
{
	if (fabs(rc->ray_dir_x) < EPSILON)
	{
		rc->step_x = 0;
		rc->side_dist_x = 0;
	}
	else if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (g->player.x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - g->player.x) * rc->delta_dist_x;
	}
}

void	calculate_y_step_and_side_dist(t_raycast *rc, t_game *g)
{
	if (fabs(rc->ray_dir_y) < EPSILON)
	{
		rc->step_y = 0;
		rc->side_dist_y = 0.0;
	}
	else if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (g->player.y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - g->player.y) * rc->delta_dist_y;
	}
}

void	calculate_step_and_side_dist(t_raycast *rc, t_game *g)
{
	calculate_x_step_and_side_dist(rc, g);
	calculate_y_step_and_side_dist(rc, g);
}
