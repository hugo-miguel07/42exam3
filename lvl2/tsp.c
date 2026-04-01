/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htavares <htavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:40:35 by htavares          #+#    #+#             */
/*   Updated: 2026/04/01 17:41:49 by htavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_point
{
	float	x;
	float	y;
}t_point;

typedef struct s_ctx
{
	float	*dist;
	int		n;
	float	best;
}t_ctx;

static float	point_dist(t_point a, t_point b)
{
	float	dx;
	float	dy;

	dx = a.x - b.x;
	dy = a.y - b.y;
	return (sqrtf(dx * dx + dy * dy));
}

static void	search_cycle(t_ctx *ctx, int start, int current,
					unsigned int visited, int count, float len)
{
	int		next;
	float	candidate;

	if (len >= ctx->best)
		return ;
	if (count == ctx->n)
	{
		candidate = len + ctx->dist[current * ctx->n + start];
		if (candidate < ctx->best)
			ctx->best = candidate;
		return ;
	}
	next = 0;
	while (next < ctx->n)
	{
		if ((visited & (1U << next)) == 0)
			search_cycle(ctx, start, next, visited | (1U << next), count + 1,
				len + ctx->dist[current * ctx->n + next]);
		next++;
	}
}

static int	read_points(t_point **points)
{
	int		capacity;
	int		n;
	t_point	*tmp;
	float	x;
	float	y;

	capacity = 16;
	n = 0;
	*points = malloc(sizeof(t_point) * capacity);
	if (!*points)
		return (-1);
	while (fscanf(stdin, " %f , %f", &x, &y) == 2)
	{
		if (n == capacity)
		{
			capacity *= 2;
			tmp = realloc(*points, sizeof(t_point) * capacity);
			if (!tmp)
				return (free(*points), *points = NULL, -1);
			*points = tmp;
		}
		(*points)[n].x = x;
		(*points)[n].y = y;
		n++;
	}
	if (ferror(stdin))
		return (free(*points), *points = NULL, -1);
	return (n);
}

int	main(void)
{
	t_point	*points;
	t_ctx	ctx;
	int		n;
	int		i;
	int		j;

	n = read_points(&points);
	if (n < 0)
		return (1);
	if (n <= 1)
	{
		fprintf(stdout, "0.00\n");
		free(points);
		return (0);
	}
	ctx.n = n;
	ctx.best = 1e30f;
	ctx.dist = malloc(sizeof(float) * n * n);
	if (!ctx.dist)
		return (free(points), 1);
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			ctx.dist[i * n + j] = point_dist(points[i], points[j]);
			j++;
		}
		i++;
	}
	search_cycle(&ctx, 0, 0, 1U, 1, 0.0f);
	fprintf(stdout, "%.2f\n", ctx.best);
	free(ctx.dist);
	free(points);
	return (0);
}

