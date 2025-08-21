/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:50:48 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:53 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	is_above_cell_valid(char **map, int r, int c);
int	is_below_cell_valid(char **map, int r, int c, int map_height);
int	is_cell_valid(char **map, int r, int c, int map_height);
char	**check_map(char **map, int map_height, int max_width);

int	is_above_cell_valid(char **map, int r, int c)
{
	int	upw;

	upw = (int)ft_strlen(map[r - 1]);
	if (c >= upw)
		return (0);
	return (map[r - 1][c] == '0' || map[r - 1][c] == '1'
		|| map[r - 1][c] == 'N' || map[r - 1][c] == 'E'
		|| map[r - 1][c] == 'W' || map[r - 1][c] == 'S');
}

int	is_below_cell_valid(char **map, int r, int c, int map_height)
{
	int	dnw;

	(void)map_height;
	dnw = (int)ft_strlen(map[r + 1]);
	if(c >= dnw)
		return(0);
	return (map[r + 1][c] == '0' || map[r + 1][c] == '1'
		|| map[r + 1][c] == 'N' || map[r + 1][c] == 'E'
		|| map[r + 1][c] == 'W' || map[r + 1][c] == 'S');
}

int	is_cell_valid(char **map, int r, int c, int map_height)
{
	if (map[r][c] != '0')
		return (1);
	if (r > 0 && !is_above_cell_valid(map, r, c))
		return (0);
	if (r < map_height - 1 && !is_below_cell_valid(map, r, c, map_height))
		return (0);
	return (1);
}

char	**check_map(char **map, int map_height, int max_width)
{
	int	r;
	int	current_width;
	int	c;

	c = 0;
	while (c < max_width)
	{
		r = 0;
		while (r< map_height)
		{
			current_width = (int)ft_strlen(map[r]);
			if (c < current_width && !is_cell_valid(map, r, c, map_height))
				return (NULL);
			r++;
		}
		c++;
	}
	return (map);
}
