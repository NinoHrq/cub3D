/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:33:47 by nharraqi          #+#    #+#             */
/*   Updated: 2025/08/21 16:35:04 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_next_line_cleanup(char **stock)
{
	int	i;

	i = 0;
	while (i < GNL_OPEN_MAX)
	{
		if (stock[i] != NULL)
		{
			free(stock[i]);
			stock[i] = NULL;
		}
		++i;
	}
}
