/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:54:51 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:48 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	ft_strlen_skip_empty_line(char *map);
void	free_game_wall(t_game *g);
char	**check_first_char(char **map, int map_height);

int	ft_strlen_skip_empty_line(char *map)
{
	int	end;

	if (!map)
		return (0);
	end = (int)ft_strlen(map) - 1;
	while (end >= 0 && (map[end] == ' ' || (map[end] >= 9 && map[end] <= 13)))
		end--;
	if (end < 0)
		return (0);
	return (end + 1);
}

void	free_game_wall(t_game *g)
{
	if (g->map)
		free_tab(g->map);
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
	exit(1);
}

char	**check_first_char(char **map, int map_height)
{
	int	i;
	int j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (map[i][j] &&(map[i][j] == ' ' || (map[i][j] >= 9 && map[i][j] <= 13)))
			j++;
		if (map[i][j] && map[i][j] != '1')
			return (NULL);
		i++;
	}
	return (map);
}
