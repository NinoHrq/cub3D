/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:31:23 by marvin            #+#    #+#             */
/*   Updated: 2025/08/20 01:48:48 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int is_map_char(int c);
int is_map_line(const char *str);

int is_map_char(int c)
{
    return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' 
        || c == 'E' || c == 'W' || is_space(c));
}
int is_map_line(const char *str)
{
    int i;
    int has_symbol;

    if(!str)
        return (0);
    i = 0;
    while(str[i] && is_space(str[i]))
        i++;
    if(!str[i])
        return (0);
    has_symbol = 0;
    while (str[i])
    {
        if (!is_map_char((unsigned char)str[i]))
            return (0);
        if(str[i] == '0' || str[i] == '1' || str[i] == '2' || str[i] == 'N' 
            || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
            has_symbol = 1;
        i++;
    }
    return (has_symbol);
        
}