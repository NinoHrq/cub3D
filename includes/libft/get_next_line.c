/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtian <mtian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:29:02 by mtian             #+#    #+#             */
/*   Updated: 2024/11/02 15:39:03 by mtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_line(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*real_line(const char *str)
{
	ssize_t	i;
	char	*dest;

	dest = NULL;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '\n' || str[i] == '\0')
	{
		i++;
	}
	dest = ft_strndup(str, i);
	return (dest);
}

static int	fill_stock_until_newline(int fd, char **stock,
		char **buffer, char **temp)
{
	int	bytes_read;

	while (!find_line(*stock))
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*buffer);
			free(*stock);
			*stock = NULL;
			return (0);
		}
		if (bytes_read == 0)
			break ;
		(*buffer)[bytes_read] = '\0';
		*temp = ft_strjoin(*stock, *buffer);
		free(*stock);
		if (*temp == NULL)
			return (free(*buffer), buffer = NULL, 0);
		*stock = *temp;
	}
	return (1);
}

static void	get_line_renew_stock(char **line, char **stock, char **temp)
{
	*line = real_line(*stock);
	*temp = ft_strchr(*stock, '\n');
	if (*temp != NULL)
	{
		*temp = ft_strdup(*temp + 1);
		free(*stock);
		*stock = *temp;
	}
	else
	{
		free(*stock);
		*stock = NULL;
	}
	if (*line != NULL && *(*line) == '\0')
	{
		free(*line);
		*line = NULL;
	}
}

char	*get_next_line(int fd, int clean)
{
	static char	*stock[GNL_OPEN_MAX] = {0};
	char		*buffer;
	char		*line;
	char		*temp;

	if (clean)
		return (get_next_line_cleanup(stock), NULL);
	if (fd < 0 || fd >= GNL_OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	if (stock[fd] == NULL)
	{
		stock[fd] = ft_strdup("");
		if (stock[fd] == NULL)
			return (free(buffer), buffer = NULL, NULL);
	}
	if (fill_stock_until_newline(fd, &stock[fd], &buffer, &temp) == 0)
		return (free(buffer), NULL);
	free(buffer);
	if (stock[fd] == NULL || *(stock[fd]) == '\0')
		return (free(stock[fd]), stock[fd] = NULL, NULL);
	get_line_renew_stock(&line, &(stock[fd]), &temp);
	return (line);
}
