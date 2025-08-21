/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_player2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:19:14 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 19:38:02 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	check_spawn_validity(char **map, int i, int j, t_game *dt);
int		neighbors_ok(char **map, int i, int j, int h);
void	last_check_spawn(char **map, int i, int *j, t_game *dt);
void	set_player_position(char **map, int i, int j, t_game *dt);
void	die_spawn(t_game *g, const char *msg);

void	die_spawn(t_game *g, const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, (int)ft_strlen(msg));
	free_game_wall(g);
}

int neighbors_ok(char **map, int i, int j, int h)
{
	int	w;
	int	upw;
	int	dnw;

	w = ft_strlen_skip_empty_line(map[i]);
	if (j > 0 && is_space((unsigned char)map[i][j - 1]))
		return (0);
	if (j + 1 < w && is_space((unsigned char)map[i][j + 1]))
		return (0);
	if (i > 0)
	{
		upw = ft_strlen_skip_empty_line(map[i - 1]);
		if (j >= upw || is_space((unsigned char)map[i - 1][j]))
			return (0);
	}
	if (i + 1 < h)
	{
		dnw = ft_strlen_skip_empty_line(map[i + 1]);
		if (j >= dnw || is_space((unsigned char)map[i + 1][j]))
			return (0);
	}
	return (1);
}

void	check_spawn_validity(char **map, int i, int j, t_game *dt)
{
	int h;
	
	h = tablen(map);
	last_check_spawn(map, i, &j, dt);
	if(!neighbors_ok(map, i, j, h))
		die_spawn(dt, "Invalid spawn position\n");
}

void	last_check_spawn(char **map, int i, int *j, t_game *dt)
{
	char c;
	
	(void)dt;
	c = map[i][*j];
	if (!(c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		die_spawn(dt, "Invalid spawn token\n");
}

void	set_player_position(char **map, int i, int j, t_game *dt)
{
	dt->player_init_direction = map[i][j];
	dt->index_player[0] = j;
	dt->index_player[1] = i;
}