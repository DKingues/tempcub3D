/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:10:20 by dicosta-          #+#    #+#             */
/*   Updated: 2025/10/30 18:52:55 by dicosta-         ###   ########.fr       */
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

int	tt_glitch_map(void)
{
	int	x;
	int	y;
	char	**temp_map;
	char	**temp_map2;

	x = 0;
	y = 0;
	temp_map = NULL;
	temp_map2 = NULL;
	temp_map2 = copy_map(temp_map2, game()->map.map);
	temp_map2[(int)game()->player.start_y][(int)game()->player.start_x] = 'G';
	while (count_zero(temp_map2) > 0)
	{
		temp_map = copy_map(temp_map, temp_map2);
		y = 0;
		while (temp_map2[y])
		{
			x = 0;
			while (temp_map2[y][x])
			{
				if (temp_map2[y][x] == 'G')
				{
					if (temp_map2[y][x - 1] != '1' && temp_map2[y][x - 1] != 'G')
						temp_map[y][x - 1] = 'G';
					if (temp_map2[y - 1][x] != '1' && temp_map2[y - 1][x] != 'G')
						temp_map[y - 1][x] = 'G';
					if (temp_map2[y + 1][x] != '1' && temp_map2[y + 1][x] != 'G')
						temp_map[y + 1][x] = 'G';
					if (temp_map2[y][x + 1] != '1' && temp_map2[y][x + 1] != 'G')
						temp_map[y][x + 1] = 'G';
				}
				x++;
			}
			y++;
		}
		game()->glitch.glitch_i++;
		temp_map2 = copy_map(temp_map2, temp_map);
	}
	if (temp_map)
		ft_free(temp_map);
	if (temp_map2)
		ft_free(temp_map2);
	return (game()->glitch.glitch_i * game()->glitch.spread_delay);
}
