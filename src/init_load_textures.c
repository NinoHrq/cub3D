/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_load_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:29:29 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 20:49:26 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	load_texture(t_game *g, t_texture *texture, char *path);
void	load_textures(t_game *g);
void	free_game(t_game *g);
void	free_textures_ulimit(t_game *g);
void	free_textures(t_game *g);

void	load_texture(t_game *g, t_texture *t, char *path)
{
	if (!g->mlx)
		tex_fail(g, "mlx not initialized\n");
	tex_load_img_or_die(g, t, path);
	tex_get_addr_or_die(g, t);
}

void	load_textures(t_game *g)
{
	load_texture(g, &g->no_texture, g->north_texture);
	load_texture(g, &g->so_texture, g->south_texture);
	load_texture(g, &g->we_texture, g->west_texture);
	load_texture(g, &g->ea_texture, g->east_texture);
}

void	free_game(t_game *g)
{
	if (g->north_texture)
		free(g->north_texture);
	if (g->south_texture)
		free(g->south_texture);
	if (g->east_texture)
		free(g->east_texture);
	if (g->west_texture)
		free(g->west_texture);
	if (g->doc)
		free_tab(g->doc);
	if (g->map)
		free_tab(g->map);
}

void	free_textures_ulimit(t_game *g)
{
	if (!g || !g->mlx)
		return ;
	free_textures(g);
	if (g->img.img)
	{
		mlx_destroy_image(g->mlx, g->img.img);
		g->img.img = NULL;
	}
	if (g->win)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	g->mlx = NULL;
}

void	free_textures(t_game *g)
{
	if (g->ea_texture.img.img)
	{
		mlx_destroy_image(g->mlx, g->ea_texture.img.img);
		g->ea_texture.img.img = NULL;
	}
	if (g->no_texture.img.img)
	{
		mlx_destroy_image(g->mlx, g->no_texture.img.img);
		g->no_texture.img.img = NULL;
	}
	if (g->we_texture.img.img)
	{
		mlx_destroy_image(g->mlx, g->we_texture.img.img);
		g->we_texture.img.img = NULL;
	}
	if (g->so_texture.img.img)
	{
		mlx_destroy_image(g->mlx, g->so_texture.img.img);
		g->so_texture.img.img = NULL;
	}
}
