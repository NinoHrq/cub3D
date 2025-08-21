/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:46:07 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 23:57:58 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

long my_strtol(const char *str, char **endptr);
int	is_digit(int c);
void	free_wrong_color(t_game *g);
void	protect_wrong_color(char **ptr, t_game *g);

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

long my_strtol(const char *str, char **endptr)
{
	long	val;

	if(!str)
		return (0);
	while (*str && is_space((unsigned char)*str))
		str++;
	val = 0;
	while (*str && is_digit((unsigned char)*str))
	{
		val = val * 10 + (*str - '0');
		str++;
	}
	if(endptr)
		*endptr = (char *)str;
	return (val);
}

void	free_wrong_color(t_game *g)
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
	exit(1);
}

void	protect_wrong_color(char **ptr, t_game *g)
{
	char	*p;

	p = *ptr;
	while (*p && is_space((unsigned char)*p))
		p++;
	if(*p != ',')
	{
		puterr("Error\nInvalid color format\n");
		free_wrong_color(g);
	}
	p++;
	while (*p && is_space((unsigned char)*p))
		p++;
	*ptr = p;
}
