/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 01:23:52 by marvin            #+#    #+#             */
/*   Updated: 2025/07/16 01:38:49 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	find_map_start(char **doc, int i);
int	found_end_map(char **doc);
int	tablen(char **tab);
int	calculate_map_size(char **doc, int start_map, int end_map);
int	no_empty_line(char **doc, int i, int is_map);

int	find_map_start(char **doc, int i)
{
	while (doc[i] && !is_map_line(doc[i]))
		i++;
	return (i);
}

int	found_end_map(char **doc)
{
	int	i;

	i = tablen(doc) - 1;
	while (i >= 0)
	{
		if (is_map_line(doc[i]))
			return (i);
		i--;
	}
	return (i);
}

int	tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	calculate_map_size(char **doc, int start_map, int end_map)
{
	(void)doc;
	if(start_map < 0 || end_map < start_map)
		return (0);
	return (end_map - start_map + 1);
}

int	no_empty_line(char **doc, int i, int is_map)
{
	int	j;

	(void)is_map;
	if(!doc || !doc[i])
		return(0);
	j = 0;
	while (doc[i][j] && is_space((unsigned char)doc[i][j]))
		j++;
	return (doc[i][j] != '\0');
}
