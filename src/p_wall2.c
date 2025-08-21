/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_wall2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:19:27 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:45 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char	**check_first_border(char **map);
void	check_null_line(char *line);
int	right_border_ok(char *line);
int	zero_surround_ok(char **map, int i, int j, int map_height);
char	**check_inner_lines(char **map, int map_height);

char	**check_first_border(char **map)
{
	int	i;
	int	j;
	int w;

	i = 0;
	while (map[i])
	{
		w = ft_strlen_skip_empty_line(map[i]);
		j = 0;
		while (j < w)
		{
			if (map[i][j] == '0' && ((j == 0 || is_space((unsigned char)map[i][j - 1]) 
				|| (j + 1 >= w || is_space((unsigned char)map[i][j + 1])))))
				return (NULL);
			j++;
		}
		i++;
	}
	return (map);
}

void	check_null_line(char *line)
{
	if (line == NULL)
	{
		printf("Error : NULL line detected\n");
		exit(1);
	}
}

int	right_border_ok(char *line)
{
	int w;
	
	w = ft_strlen_skip_empty_line(line);
	if (w == 0)
		return (1);
	return (line[w - 1] == '1');
}

int	zero_surround_ok(char **map, int i, int j, int map_height)
{
	int w;
	int	upw;
	int	dnw;

	w = ft_strlen_skip_empty_line(map[i]);
	if (j == 0 || is_space((unsigned char)map[i][j - 1]))
		return (0);
	if (j + 1 >= w || is_space((unsigned char)map[i][j + 1]))
		return (0);
	if (i == 0)
		return (0);
	upw = ft_strlen_skip_empty_line(map[i - 1]);
	if (j >= upw || is_space((unsigned char)map[i - 1][j]))
		return (0);
	if (i + 1 >= map_height)
		return (0);
	dnw = ft_strlen_skip_empty_line(map[i + 1]);
	if (j >= dnw || is_space((unsigned char)map[i + 1][j]))
		return (0);

	return (1);
}


char	**check_inner_lines(char **map, int map_height)
{
	int	i;
	int	j;
	int	map_width;

	i = 1;
	while (i < map_height - 1)
	{
		check_null_line(map[i]);
		map_width = ft_strlen_skip_empty_line(map[i]);
		if (!right_border_ok(map[i]))
			return (NULL);
		j = 0;
		while (j < map_width)
		{
			if (map[i][j] == '0' && !zero_surround_ok(map, i, j, map_height)) 
					return (NULL);
			j++;
		}
		i++;
	}
	return (map);
}
