/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:53:58 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:49:33 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	validate_identifier(char *line);
int	parse_doc(char **doc, int start_map);
void	exit_properly_parsing(t_game *g);


int	parse_doc(char **doc, int start_map)
{
	int	i;

	i = 0;
	while (doc[i])
	{
		if (i >= start_map)
			break ;
		if (validate_identifier(doc[i]))
			return (1);
		i++;
	}
	return (0);
}

int	validate_identifier(char *line)
{
	int	j;

	if(!line)
		return(0);
	if (ft_strncmp(line, "NO ", 3) == 0 && ft_strncmp(line, "SO ", 3) == 0
		&& ft_strncmp(line, "WE ", 3) == 0 && ft_strncmp(line, "EA ", 3) == 0
		&& ft_strncmp(line, "F ", 2) == 0 && ft_strncmp(line, "C ", 2) == 0)
		return (0);
	
	j = 0;
	while (line[j] && line[j] <= 32)
		j++;
	if (line[j] != '\0')
	{
			printf("\n\n\tError\n Invalid identifier \"%s\"\n\n\n", line);
			return (1);
	}
	return (0);
}

void	exit_properly_parsing(t_game *g)
{
	if (g->north_texture)
		free(g->north_texture);
	if (g->south_texture)
		free(g->south_texture);
	if (g->west_texture)
		free(g->west_texture);
	if (g->east_texture)
		free(g->east_texture);
	if (g->map)
		free_tab(g->map);
	if (g->doc)
		free_tab(g->doc);
	exit(1);
}
