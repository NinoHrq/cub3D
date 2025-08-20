/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:52:38 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:50:04 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

size_t s_len(const char *s);
int id_code(const char *s);
void scan_identifiers(t_game *g, int seen[6]);

size_t s_len(const char *s)
{
    size_t i;

    i = 0;
    while(s && s[i])
        ++i;
    return(i);
}

int id_code(const char *s)
{
    if (!s)
		return (-1);
	if (ft_strncmp(s, "NO ", 3) == 0)
		return (0);
	if (ft_strncmp(s, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(s, "WE ", 3) == 0)
		return (2);
	if (ft_strncmp(s, "EA ", 3) == 0)
		return (3);
	if (ft_strncmp(s, "F ", 2) == 0)
		return (4);
	if (ft_strncmp(s, "C ", 2) == 0)
		return (5);
	return (-1);
}

void scan_identifiers(t_game *g, int seen[6])
{
    int i;
    int code;
    char *line;

    i = 0;
    while(g->doc[i])
    {
        line = skip_spaces(g->doc[i]);
        code = id_code(line);
        if (code >= 0)
        {
            if (seen[code])
                free_game_texture(g, "Duplicate identifier\n");
            seen[code] = 1;
        }
        i++;
    }
}