/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:53:14 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:41 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char **parse_wall(char **map, t_game *g);
int	found_max_width(char **map);
char	**check_top_border(char **map);
char	**check_bottom_border(char **map, int map_height);
void	die_wall(t_game *g, const char *msg);

char **parse_wall(char **map, t_game *g)
{
	int	map_height;
	int	max_width;

	map_height = tablen(map);
	max_width = found_max_width(map);
	if (!check_top_border(map))
		die_wall(g, "Invalid top border\n");
	if (!check_bottom_border(map, map_height))
		die_wall(g, "Invalid bottom border\n");
	if (!check_first_border(map))
		die_wall(g, "Open space near '0' (left/right)\n");
	if (!check_inner_lines(map, map_height))
		die_wall(g, "Invalid inner lines\n");
	if (!check_map_validity(map, map_height, max_width))
		die_wall(g, "Invalid vertical adjacency\n");
	if (!check_map(map, map_height, max_width))
		die_wall(g, "Invalid map cells\n");
	if (!check_first_char(map, map_height))
		die_wall(g, "Left border must be wall\n");
	return (map); 
}

int	found_max_width(char **map)
{
	int	m;
	int w;
	int	i;

	i = 0;
	m = 0;
	while (map[i])
	{
		w = ft_strlen_skip_empty_line(map[i]);
		if (w > m)
			m = w;
		i++;
	}
	return (m);
}

char	**check_top_border(char **map)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (!is_space((unsigned char)map[0][j]) && map[0][j] != '1')
			return (NULL);
		j++;
	}
	return (map);
}

char	**check_bottom_border(char **map, int map_height)
{
	int	j;

	j = 0;
	while (map[map_height - 1][j])
	{
		if (!is_space((unsigned char)map[map_h - 1][j]) && map[map_h - 1][j] != '1')
			return (NULL);
		j++;
	}
	return (map);
}

void	die_wall(t_game *g, const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, (int)ft_strlen(msg));
	free_game_wall(g);
}