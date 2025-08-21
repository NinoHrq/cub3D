/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:55:42 by marvin            #+#    #+#             */
/*   Updated: 2025/08/19 16:10:53 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void parsing_config(t_game *g, char **doc);
void parser_ctx_zero(t_parser_context *ctx);
void parse_identifiers(t_game *g, char **doc, t_parser_context *ctx);
void	check_identifiers(t_game *g, int count);
void	map_from_doc(t_game *g, char **doc, int start_map, int map_size);

void parsing_config(t_game *g, char **doc)
{
    t_parser_context ctx;

    parser_ctx_zero(&ctx);
    parse_identifiers(g, doc, &ctx);
    check_identifiers(g, ctx.x);
    ctx.start_map = find_map_start(doc, ctx.i);
    ctx.end_map = found_end_map(doc);
    if (doc[ctx.start_map] == NULL)
		free_game_texture(g, "\n\nNot seeing any map here\n\n\n");
	ctx.map_size = calculate_map_size(doc, ctx.start_map, ctx.end_map);
	map_from_doc(g, doc, ctx.start_map, ctx.map_size);
	g->start_map = ctx.start_map;

}

void parser_ctx_zero(t_parser_context *ctx)
{
	ctx->i = 0;
    ctx->j = 0;
    ctx->x = 0;
    ctx->start_map = 0;
	ctx->end_map = 0;
	ctx->map_size = 0;
}

void parse_identifiers(t_game *g, char **doc, t_parser_context *ctx)
{
    while (doc[ctx->i] && ctx->j < 6)
    {
        doc[ctx->i] = parse_doc_line(doc[ctx->i]);
        if (ft_strncmp(doc[ctx->i], "NO ", 3) == 0 || ft_strncmp(doc[ctx->i],
				"SO ", 3) == 0 || ft_strncmp(doc[ctx->i], "WE ", 3) == 0
			|| ft_strncmp(doc[ctx->i], "EA ", 3) == 0)
        {
            handle_texture_directive(g, ctx, doc[ctx->i]);
            ctx->j++;
            ctx->i++;
        }
        else if (ft_strncmp(doc[ctx->i], "F ", 2) == 0 
            || ft_strncmp(doc[ctx->i], "C ", 2) == 0)
            {
                handle_color_directive(g, ctx, doc[ctx->i]);
                ctx->j++;
                ctx->i++;
            }
            else
                ctx->i++;
    }
}

void	check_identifiers(t_game *g, int count)
{
	if (count != 6)
		free_game_texture(g,
			"\n\nMissing Identifier Texture\n\n\n");
	if (g->north_texture == NULL)
		free_game_texture(g,
			"\n\nMissing North Texture\n\n\n");
	if (g->south_texture == NULL)
		free_game_texture(g,
			"\n\nMissing South Texture\n\n\n");
	if (g->west_texture == NULL)
		free_game_texture(g,
			"\n\nMissing West Texture\n\n\n");
	if (g->east_texture == NULL)
		free_game_texture(g,
			"\n\nMissing East Texture\n\n\n");
	if (valid_texture(g) == false)
		free_game_texture(g, "\n\nInvalid texture path(s)\n\n");
}

void	map_from_doc(t_game *g, char **doc, int start_map, int map_size)
{
	int	i;
	int	j;

	g->map = (char **)malloc(sizeof(char *) * (map_size + 1));
	if (!g->map)
		free_game_texture(g, "\n Allocation failed for map\n\n");
	i = start_map;
	j = 0;
	while (doc[i] && j < map_size)
	{
		g->map[j] = ft_strdup(doc[i]);
		if (!g->map[j])
		{
			while (j-- > 0)
				free(g->map[j]);
			free(g->map);
			g->map = NULL;
			free_game_texture(g, "\n Allocation failed while copying the map\n\n");
		}
		j++;
		i++;
	}
	g->map[j] = NULL;
}
