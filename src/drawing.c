/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:05:50 by marvin            #+#    #+#             */
/*   Updated: 2025/08/19 14:35:58 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	move_player(t_game *g);
void	draw_floor_and_ceiling(t_game *g);
void	raycast(t_game *g);
int		drawing(t_game *g);

void	move_player(t_game *g)
{
	t_movement	m;

	init_movement(&m);
	handle_forward_backward_movement(g, &m);
	handle_left_right_movement(g, &m);
	handle_rotation(g, &m);
}

void	draw_floor_and_ceiling(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&g->img, x, y, g->c_color);
			else
				put_pixel(&g->img, x, y, g->f_color);
			x++;
		}
		y++;
	}
}

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

int	drawing(t_game *g)
{
	move_player(g);
	ft_memset(g->img.addr, 0, (size_t)g->img.line_length * HEIGHT);
	draw_floor_and_ceiling(g);
	raycast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}