/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:58:57 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 23:25:50 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	handle_color_directive(t_game *g, t_parser_context *ctx, char *line);
int	parse_color_line(char *s);
void rgb_parse_triplet(char *s, int color[3], t_game *g);

void rgb_parse_triplet(char *s, int color[3], t_game *g);
{
    char    *ptr;
    char    *end;
    int     i;
    long    val;

    ptr = s;
    i = 0;
    while (i < 3)
    {
        while (*ptr && is_space((unsigned char)*ptr))
            ptr++;
        val = my_strtol(ptr, &end, 10);
        if (ptr == end || val < 0 || val > 255)
        {
            puterr("Error\nInvalid color component\n");
            free_wrong_color(g);
        }
        color[i] = (int)val;
        ptr = end;
        if (i < 2)
            protect_wrong_color(&ptr, g);
        i++;
    }
}

void	handle_color_directive(t_game *g, t_parser_context *ctx, char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
    {
        if (parse_color_line(line))
        {
            puterr("Error\nWrong floor format\n");
            free_wrong_color(g);
        }
        rgb_parse_triplet(line + 2, game->floor_color, g);
        ctx->x++;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        if (parse_color_line(line))
        {
            puterr("Error\nWrong ceiling format\n");
            free_wrong_color(g);
        }
        rgb_parse_triplet(line + 2, game->ceiling_color, g);
        ctx->x++;
    }
}

int	parse_color_line(char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] <= 32)
		i++;
	if (!s[i])
		return (1);
	while (s[i] && s[i] > 32)
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ',' && s[i] != ' ')
			return (1);
		i++;
	}
	while (s[i] && s[i] <= 32)
		i++;
	if (s[i] != '\0')
		return (1);
	return (0);
}
