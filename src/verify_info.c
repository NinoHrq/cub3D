/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:54:55 by nharraqi          #+#    #+#             */
/*   Updated: 2025/08/21 15:55:40 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void verify_info(t_game *g);
void free_game_texture(t_game *g, char *txt);
void	free_tab(char **tab);

void verify_info(t_game *g)
{
	int i;
	int seen[6];
	
	if(!g || !g->doc)
		return;
	i = 0;
	while (i < 6)
		seen[i++] = 0;
	scan_identifiers(g, seen);
	i = 0;
	while (i < 6)
	{
		if(!seen[i])
			free_game_texture(g, "\n Wrong number of identifier \n");
		i++;
	}
}

void free_game_texture(t_game *g, char *txt)
{
	printf("Error\n");
	printf("%s", txt);
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
