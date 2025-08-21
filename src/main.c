/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:42:11 by nharraqi          #+#    #+#             */
/*   Updated: 2025/08/21 15:54:31 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void print_usage(void);
static int run_game(const char *path);

int main(int ac, char **av)
{
    
    if(ac != 2)
    {
        print_usage();
        return(1);
    }
    if (parse_av(av[1]) != 0)
    {
        print_usage();
        return(1);
    }
    return(run_game(av[1]));
}

static int run_game(const char *path)
{
    t_game  g;

    game_init(&g, path);
    if(!g.map)
        return(1);
    closing(&g);
    mlx_loop_hook(g.mlx, drawing, &g);
    mlx_loop(g.mlx);
    if(g.map)
        free_tab(g.map);
    return(0);
}

static void print_usage(void)
{
    const char msg[] = "\n\n\tUSAGE : \"./cub3D\" \"file.cub\"\n\n\n";
    write(2, msg, sizeof(msg) - 1);
}