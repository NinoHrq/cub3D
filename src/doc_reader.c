/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharraqi <nharraqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:50:51 by nharraqi          #+#    #+#             */
/*   Updated: 2025/06/10 15:55:13 by nharraqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char **get_doc(char *filename);
static int	ensure_capacity(t_doc *ctx);
int ctx_init(t_doc *ctx, const char *filename);
char **allocate_map(int size);
char **reallocate_map(char **map, int pre_size, int new_size);


char **get_doc(const char *filename)
{
	t_doc ctx;
	
	if(ctx_init(&ctx, filename))
		return(NULL);
	ctx.line = get_next_line(ctx.fd);
	while(ctx.line)
	{
		if(ensure_capacity(&ctx))
		{
			free(ctx.line);
			free_tab(ctx.map);
			closing_fd(&ctx);
			return (NULL);
		}
		process_line(&ctx);
		ctx.j++;
		free(ctx.line);
		ctx.line = get_next_line(ctx.fd);
	}
	ctx.map[ctx.j] = NULL;
	closing_fd(&ctx);
	return(ctx.map);	
}

static init ensure_capacity(t_doc *ctx)
{
	char	**old;
	char	**new_map;

	if(ctx->j < ctx->size - 1)
		return(0);
	old = ctx->map;
	new_map = reallocate_map(old, ctx->size, ctx->size * 2);
	if (!new_map)
		return (1);
	ctx->new_map = new_map;
	ctx->size *= 2;
	return (0);
}

int init_ctx(t_doc *ctx, const char *filename)
{
	initialize_context(ctx, (char *)filename);
	if (ctx->fd < 0)
	{
		printf("\n can't open the file in init_ctx \n");
		return (1);
	}
	ctx->map = allocate_map(ctx->size);
	if (!ctx->map)
	{
		printf("\n Allocate map failed \n");
		return (1);
	}
	ctx->map[0] = NULL;
	return(0);
}

char **allocate_map(int size)
{
	char **map;
	int i;
	
	map = (char **)malloc(sizeof(char *) * size);
	if (!map)
	{
		printf("\n Malloc Failed in allocate_map \n");
		return(NULL);
	}
	i = 0;
	while (i < size)
		map[i++] = NULL;
	return (map);
}

char **reallocate_map(char **map, int pre_size, int new_size)
{
	char **new_map;
	int i;
	
	new_map = (char **)malloc(sizeof(char *) * new_size);
	if (!new_map)
	{
		printf("\n Malloc Failed in reallocate_map \n");
		return(NULL);
	}
	i = 0;
	while (i < pre_size)
	{
		new_map[i] = map[i];
		i++;
	}
	while (i < new_size)
		new_map[i++] = NULL;
	free(map);
	return (new_map);
}
