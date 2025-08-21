/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:17:05 by nharraqi          #+#    #+#             */
/*   Updated: 2025/08/21 15:55:22 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	parse_av(char *filename);
void verif_name(char *s);
char *extracting_extension(char *s);
int verif_extension(char *ext);

int	parse_av(char *filename)
{
	char 	*extension;
	
	verif_name(filename);
	extension = extracting_extension(filename);
	return(verif_extension(extension));
}

void verif_name(char *s)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (i == 0)
				exit(1);
			else if (s[i - 1] == '/')
				exit(1);
		}
		i++;
	}
}


char *extracting_extension(char *s)
{
	char *dot;
	char *ext;

	if(!s)
		return (NULL);
	dot = ft_strrchr(s, '.');
	if (!dot)
		return (NULL);
	ext = ft_strdup(dot);
	return (ext);
}

int verif_extension(char *ext)
{
	int	res;

	if (!ext)
		return(1);
	res = (ft_strncmp(ext, ".cub", 5) == 0);
	free(ext);
	if (res)
		return(0);
	return (1);
}
