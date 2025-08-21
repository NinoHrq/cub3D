/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initcore2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:53:06 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 21:21:07 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_player_pos(t_game *g);
void	init_mlx(t_game *g);
void	init_colors(t_game *g);
static int	rgb_to_int(const int tab[3]);
void	initialize_context(t_doc *ctx, const char *filename);

void	init_player_pos(t_game *g)
{
	if (!g->map)
		return ;
	g->player.x = g->index_player[0] + 0.5;
	g->player.y = g->index_player[1] + 0.5;
	if (g->player_init_direction == 'N')
		g->player.angle = 3 * PI / 2;
	else if (g->player_init_direction == 'S')
		g->player.angle = PI / 2;
	else if (g->player_init_direction == 'E')
		g->player.angle = 0;
	else if (g->player_init_direction == 'W')
		g->player.angle = PI;
	g->player.dir_x = cos(g->player.angle);
	g->player.dir_y = sin(g->player.angle);
	g->player.plane_x = -g->player.dir_y * 0.66;
	g->player.plane_y = g->player.dir_x * 0.66;
}

void	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
	{
		printf("Erreur : Impossible d'initialiser la bibliothèque MLX.\n");
		exit(EXIT_FAILURE);
	}
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (!g->win)
	{
		printf("Impossible de créer la fenêtre (dimensions : %d x %d).\n",
			WIDTH, HEIGHT);
		exit(EXIT_FAILURE);
	}
	g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img.img)
	{
		printf("Impossible de créer l'image (dimensions : %d x %d).\n", WIDTH,
			HEIGHT);
		exit(EXIT_FAILURE);
	}
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
}

void	init_colors(t_game *g)
{
	g->f_color = rgb_to_int(g->floor_color);
	g->c_color = rgb_to_int(g->ceiling_color);
	if (g->f_color == -1 || g->c_color == -1)
	{
		printf("\n\nError: Invalid floor or ceiling color\n\n");
		exit(EXIT_FAILURE);
	}
}

static int	rgb_to_int(const int tab[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (tab[i] < 0 || tab[i] > 255)
			return (-1);
		i++;
	}
	return ((tab[0] << 16) | (tab[1] << 8) | tab[2]);
}

void	initialize_context(t_doc *ctx, const char *filename)
{
	ctx->fd = open(filename, O_RDONLY);
	ctx->map = NULL;
	ctx->line = NULL;
	ctx->i = 0;
	ctx->j = 0;
	ctx->size = 8;
}