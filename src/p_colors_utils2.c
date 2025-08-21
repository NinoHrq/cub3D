/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_colors_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:30:59 by marvin            #+#    #+#             */
/*   Updated: 2025/07/15 18:48:30 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	get_digit_value(char c);
int	is_valid_digit(int digit, int base);
void	free_wrong_color(t_game *g);

int	get_digit_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	is_valid_digit(int digit, int base)
{
	return (digit >= 0 && digit < base);
}
