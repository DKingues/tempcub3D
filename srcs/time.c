/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:10:20 by dicosta-          #+#    #+#             */
/*   Updated: 2025/10/30 18:09:11 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

long get_elapsed_sec(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return (current.tv_sec - game()->game_start);
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * (long)1e3 + (tv.tv_usec / 1e3));
}

int	count_zero(char **map)
{
	int	blocks_to_glitch;
	int y;
	int x;

	blocks_to_glitch = 0;
	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'O' || map[y][x] == 'C')
				blocks_to_glitch++;
			x++;
		}
		y++;
	}
	return (blocks_to_glitch);
}