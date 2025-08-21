/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 01:20:40 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 21:55:04 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_movement(t_movement *m);
void	handle_forward_backward_movement(t_game *g, t_movement *m);
void	move_forward_backward(t_game *g, t_movement *m, int dir);
int	is_near_wall(t_game *g, double nx, double ny);
int	is_blocking(const t_game *g, int y, int x);

void	init_movement(t_movement *m)
{
	m->move_speed = 0.1;
	m->rot_speed = 0.05;
	m->new_x = 0.0;
	m->new_y = 0.0;
	m->old_dir_x = 0.0;
	m->old_plane_x = 0.0;
}

void	handle_forward_backward_movement(t_game *g, t_movement *m)
{
	if (g->player.key_up)
		move_forward_backward(g, m, 1);
	if (g->player.key_down)
		move_forward_backward(g, m, -1);
}

void	move_forward_backward(t_game *g, t_movement *m, int dir)
{
	double	spd;

	spd = m->move_speed;
	m->new_x = g->player.x + g->player.dir_x * spd * dir;
	m->new_y = g->player.y + g->player.dir_y * spd * dir;
	if (!is_near_wall(g, m->new_x, g->player.y))
		g->player.x = m->new_x;
	if (!is_near_wall(g, g->player.x, m->new_y))
		g->player.y = m->new_y;
}

int	is_near_wall(t_game *g, double nx, double ny)
{
	double	r;

	r = PLAYER_RADIUS;
	if (is_blocking(g, (int)(ny - r), (int)(nx - r)))
		return (1);
	if (is_blocking(g, (int)(ny - r), (int)(nx + r)))
		return (1);
	if (is_blocking(g, (int)(ny + r), (int)(nx - r)))
		return (1);
	if (is_blocking(g, (int)(ny + r), (int)(nx + r)))
		return (1);
	return (0);
}

int	is_blocking(const t_game *g, int y, int x)
{
	int		h;
	int		rowlen;
	char	c;

	if (y < 0 || x < 0)
		return(1);
	h = 0;
	while (g->map[h])
		h++;
	if (y >= h)
		return (1);
	rowlen = (int)ft_strlen(g->map[y]);
	if (x >= rowlen)
		return (1);
	c = g->map[y][x];
	return(!(c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'));
}