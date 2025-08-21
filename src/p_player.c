/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:03:30 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 19:38:30 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx);
void	check_multiple_spawns(int *d_flag, t_game *dt);
void	player_spawn(char **map, t_game *dt);
int		map_char_kind(char c);

void	process_spawn_tile(char **map, int i, int j, t_spawn_ctx *ctx)
{
	check_multiple_spawns(&ctx->d_flag, ctx->dt);
	check_spawn_validity(map, i, j, ctx->dt);
	set_player_position(map, i, j, ctx->dt);
	ctx->d_flag++;
}

void	process_tile(char **map, int i, int j, t_spawn_ctx *ctx)
{
	char	tile;

	check_invalid_cases(map, i, j, ctx->dt);
	tile = map_char_kind(map[i][j]);
	if (tile == 2)
		process_spawn_tile(map, i, j, ctx);
}

void	player_spawn(char **map, t_game *dt)
{
	int			i;
	int			j;
	t_spawn_ctx	ctx;

	i = 0;
	ctx.dt = dt;
	ctx.d_flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			process_tile(map, i, j, &ctx);
			j++;
		}
		i++;
	}
	if (ctx.d_flag == 0)
		die_spawn(dt, "No spawn detected\n");
}

void	check_multiple_spawns(int *d_flag, t_game *dt)
{
	if (*d_flag > 0)
		die_spawn(dt, "Miltiple spawn points\n");
}

void	check_invalid_cases(char **map, int i, int j, t_game *dt)
{
	char c;
	int k;
	
	c = map[i][j];
	if(c == '\0')
		return ;
	if (is_space((unsigned char)c))
		return ;
	k = map_char_kind(c);
	if (k == 0)
		die_spawn(dt, "Invalid character in map\n");
}

int	map_char_kind(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (2);
	return (0);
}
