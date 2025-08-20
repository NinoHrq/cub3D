/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:33:40 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:50 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	is_valid_tile(char c);
int	check_up_tile(char **map, int r, int c);
int	check_down_tile(char **map, int r, int c, int map_height);
char	**check_map_validity(char **map, int map_height, int max_width);

int	is_valid_tile(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'S');
}

int	check_up_tile(char **map, int r, int c)
{
	int	upw;

	if (r == 0)
		return (1);
	upw = ft_strlen(map[r - 1]);
	if (c >= upw || !is_valid_tile(map[r - 1][c]))
		return (0);
	return (1);
}

int	check_down_tile(char **map, int r, int c, int map_height)
{
	int	dnw;

	if (r >= map_height - 1)
		return (1);
	dnw = ft_strlen(map[r + 1]);
	if (c >= dwn || !is_valid_tile(map[r + 1][c]))
		return (0);
	return (1);
}

char	**check_map_validity(char **map, int map_height, int max_width)
{
	int	c;
	int	r;
	int	current_width;

	c = 0;
	while (c < max_width)
	{
		r = 0;
		while (r < map_height)
		{
			current_width = (int)ft_strlen(map[r]);
			if (c < current_width && map[r][c] == '0')
				if (!check_up_tile(map, r, c) || !check_down_tile(map, r, c,
						map_height))
					return (NULL);
			r++;
		}
		c++;
	}
	return (map);
}