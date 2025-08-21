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

char **get_doc(const char *filename);
int	ensure_capacity(t_doc *ctx);
int ctx_init(t_doc *ctx, const char *filename);
char **allocate_map(int size);
char **reallocate_map(char **map, int pre_size, int new_size);


char **get_doc(const char *filename)
{
	t_doc ctx;
	
	if(ctx_init(&ctx, filename))
		return(NULL);
	ctx.line = get_next_line(ctx.fd, 0);
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
		ctx.line = get_next_line(ctx.fd, 0);
	}
	ctx.map[ctx.j] = NULL;
	closing_fd(&ctx);
	return(ctx.map);	
}

int ensure_capacity(t_doc *ctx)
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

int ctx_init(t_doc *ctx, const char *filename)
{
	initialize_context(ctx, filename);
	if (ctx->fd < 0)
	{
		fprintf(stderr, "Error: cannot open '%s': %s\n", filename, strerror(errno));
		printf("Error\n");
		printf("\n can't open the file in ctx_init \n");
		return (1);
	}
	ctx->map = allocate_map(ctx->size);
	if (!ctx->map)
	{
		fprintf(stderr, "Allocate map failed\n");
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
