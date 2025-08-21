/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_close.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 00:58:41 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 20:05:39 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *g);
int	key_release(int keycode, t_game *g);
void	closing(t_game *g);
int	ft_close(t_game *g);

int	key_press(int keycode, t_game *g)
{
	if (keycode == ESC || keycode == QUIT)
		return (ft_close(g));
	if (keycode == W)
		g->player.key_up = TRUE;
	if (keycode == S)
		g->player.key_down = TRUE;
	if (keycode == A)
		g->player.key_left = TRUE;
	if (keycode == D)
		g->player.key_right = TRUE;
	if (keycode == LEFT)
		g->player.left_rotate = TRUE;
	if (keycode == RIGHT)
		g->player.right_rotate = TRUE;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == W)
		g->player.key_up = FALSE;
	if (keycode == S)
		g->player.key_down = FALSE;
	if (keycode == A)
		g->player.key_left = FALSE;
	if (keycode == D)
		g->player.key_right = FALSE;
	if (keycode == LEFT)
		g->player.left_rotate = FALSE;
	if (keycode == RIGHT)
		g->player.right_rotate = FALSE;
	return (0);
}

void	closing(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, QUIT, ESC, ft_close, g);
}

int	ft_close(t_game *g)
{
	if (g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
	}
	free_textures(g);
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
	}
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free_game(g);
	exit(0);
	return (0);
}
