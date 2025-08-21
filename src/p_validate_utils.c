/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:26:51 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 01:22:53 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

bool	valid_texture(t_game *g);
bool	has_xpm_suffix(const char *path);
int	check_texture_path(const char *path);
double	safe_delta(double ray);

bool	valid_texture(t_game *g)
{
	if (!g->north_texture || !g->south_texture
		|| !g->west_texture || !g->east_texture)
		return (false);
	if (!has_xpm_suffix(g->north_texture) || !has_xpm_suffix(g->south_texture)
		|| !has_xpm_suffix(g->west_texture) || !has_xpm_suffix(g->east_texture))
		return (false);
	if (check_texture_path(g->north_texture)
		|| check_texture_path(g->south_texture)
		|| check_texture_path(g->west_texture)
		|| check_texture_path(g->east_texture))
		return (false);
	return (true);
}

bool	has_xpm_suffix(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + (len - 4), ".xpm", 4) == 0);
}

int	check_texture_path(const char *path)
{
	int	fd;

	if (!path || !*path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

double	safe_delta(double ray) // jle met la pour pas créer un autre fichier mais c'est pour le raycast1
{
	if (fabs(ray) < EPSILON)
		return (1e30);
	return (fabs(1.0 / ray));
}
