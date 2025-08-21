/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:25:29 by marvin            #+#    #+#             */
/*   Updated: 2025/08/21 01:26:17 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	assign_texture(t_game *g, t_parser_context *ctx, char c, char *doc);
char	**texture_slot(t_game *g, char id);

char	**texture_slot(t_game *g, char id)
{
	if (id == 'N')
		return (&g->north_texture);
	if (id == 'S')
		return (&g->south_texture);
	if (id == 'W')
		return (&g->west_texture);
	if (id == 'E')
		return (&g->east_texture);
	return (NULL)
}

void	assign_texture(t_game *g, t_parser_context *ctx, char id, char *doc)
{
	char	**slot;
	char	*p;

	(void)ctx;
	slot = texture_slot(g, id);
	if (!slot)
		free_game_texture(g, "Error\nUnknown texture id\n");
	p = doc + 2;
	while(*p && is_space((unsigned char)*p))
		p++;
	if(*p == '\0')
		free_game_texture(g, "Error\nMissing texture path\n");
	if (*slot != NULL)
		free_game_texture(g, "Error\nDuplicate texture identifier\n");
	*slot = ft_strdup(p);
	if (!*slot)
		free_game_texture(g, "Error\nAllocation failed for texture path\n");
}
