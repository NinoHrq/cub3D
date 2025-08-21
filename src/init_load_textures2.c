/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_load_textures2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:49:56 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 21:04:49 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void puterr(const char *s);
void tex_fail(const char *s);
void tex_load_img_or_die(t_game *g, t_texture *t, char *path);
void tex_get_addr_or_die(t_game *g, t_texture *t);

void puterr(const char *s)
{
    write(2, s, (int)ft_strlen(s));
}

void tex_fail(const char *s)
{
    puterr("Error\n");
    puterr(msg);
    free_textures_ulimit(g);
    free_game(g);
    exit(EXIT_FAILURE);
}

void tex_load_img_or_die(t_game *g, t_texture *t, char *path)
{
    if (!path || *path == '\0')
        tex_fail(g, "Invalid texture path\n");
    t->img.img = mlx_xpm_file_to_image(g->mlx, path, &t->width, &t->height);
    if(!t->img.img)
        tex_fail(g, "Failed to load texture\n");
}

void tex_get_addr_or_die(t_game *g, t_texture *t)
{
    t->img.addr = mlx_get_data_addr(t->img.img; &t->img.bits_per_pixel, &t->img.line_length, &t->img.endian);
    if(!t->img.addr)
        tex_fail(g, "mlx_get_data_addr failed\n");
}
