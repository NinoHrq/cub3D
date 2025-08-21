/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:30:03 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 22:09:45 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	handle_left_right_movement(t_game *g, t_movement *m);
void	move_left_right(t_game *g, t_movement *m, int dir);
void	handle_rotation(t_game *g, t_movement *m);
void	rotate_player(t_game *g, t_movement *m, int dir);
void	put_pixel(t_ig *img, int x, int y, int color);

void	handle_left_right_movement(t_game *g, t_movement *m)
{
	if (g->player.key_left)
		move_left_right(g, m, -1);
	if (g->player.key_right)
		move_left_right(g, m, 1);
}

void	move_left_right(t_game *g, t_movement *m, int dir)
{
	double	spd;

	spd = m->move_speed;
	m->new_x = g->player.x + g->player.plane_x * spd * dir;
	m->new_y = g->player.y + g->player.plane_y * spd * dir;
	if (!is_near_wall(g, m->new_x, g->player.y))
		g->player.x = m->new_x;
	if (!is_near_wall(g, g->player.x, m->new_y))
		g->player.y = m->new_y;
}

void	handle_rotation(t_game *g, t_movement *m)
{
	if (g->player.left_rotate)
		rotate_player(g, m, -1);
	if (g->player.right_rotate)
		rotate_player(g, m, 1);
}

void	rotate_player(t_game *g, t_movement *m, int dir)
{
	double cs;
	double sn;
	
	cs = cos(dir * m->rot_speed);
	sn = sin(dir * m->rot_speed);
	m->old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cs - g->player.dir_y * sn;
	g->player.dir_y = m->old_dir_x * sn	+ g->player.dir_y * cs;
	m->old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cs - g->player.plane_y * sn;
	g->player.plane_y = m->old_plane_x * sn	+ g->player.plane_y * cs;
}

void	put_pixel(t_ig *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
