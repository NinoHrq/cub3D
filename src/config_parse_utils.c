/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:06:22 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:48:44 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int is_space(int c);
char tex_id_from_line(const char *line);
char **slot_by_id(t_game *g, char id);
char	*parse_doc_line(char *str);
void	handle_texture_directive(t_game *g, t_parser_context *ctx,
		char *line);

int is_space(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
char tex_id_from_line(const char *line)
{
	if (!line)
		return(0);
	if (strncmp(line, "NO ", 3) == 0)
		return ('N');
	if (strncmp(line, "SO ", 3) == 0)
		return ('S');
	if (strncmp(line, "WE ", 3) == 0)
		return ('W');
	if (strncmp(line, "EA ", 3) == 0)
		return ('E');
	return (0);	
}

char **slot_by_id(t_game *g, char id)
{
	if (id == 'N')
		return (&g->north_texture);
	if (id == 'S')
		return (&g->south_texture);
	if (id == 'W')
		return (&g->west_texture);
	if (id == 'E')
		return (&g->east_texture);
	return(NULL);
}

char	*parse_doc_line(char *str)
{
	int		start;
	int		end;
	size_t	len;
	char	*tmp;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || (str[start] >= 9 && str[start] <= 13)))
		start++;
	end = (int)ft_strlen(str) - 1;
	while (end >= start
		&& (str[end] == ' ' || (str[end] >= 9 && str[end] <= 13)))
		end--;
	if (end < start)
		len = 0;
	else
		len = (size_t)(end - start + 1);
	tmp = ft_substr(str, start, len);
	if (!tmp)
		return (str);
	free(str);
	return (tmp);
}

void	handle_texture_directive(t_game *g, t_parser_context *ctx,
		char *line)
{
	char	id;
	char	**slot;

	(void)ctx;
	id = tex_id_from_line(line);
	if(!id)
		return;
	slot = slot_by_id(g, id);
	if(slot && *slot != NULL)
		free_game_texture(g, "Duplicate texture identifier\n\n");
	assign_texture(g, ctx, id, line);
}
