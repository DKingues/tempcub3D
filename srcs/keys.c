/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:42:20 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/10/22 17:50:30 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *nada)
{
	(void)nada;
	int last_x;
	if (keycode == XK_Escape)
		clean_exit(NULL);
	if(game()->state == MENU || game()->state == OPT_M || game()->state == CTRL_M)
		return (0);
	if(game()->state == GAME)
		game_press(keycode);
	else if (keycode == XK_p)
	{
		mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
		mlx_mouse_move(game()->mlx, game()->win, game()->mouse.x, 1070);
		last_x = game()->mouse.x;
		game_move(&last_x);
		game()->state = GAME;
		lighten(game()->canvas, 0.4);
	}
	return (0);
}

void	game_press(int keycode)
{
	if (keycode == XK_p)
		pause_game();
	if (keycode == XK_Shift_L)
		game()->player.diff = 1;
	if (keycode == XK_d)
		game()->player.moving_d = 1;
	if (keycode == XK_s)
		game()->player.moving_s = 1;
	if (keycode == XK_a)
		game()->player.moving_a = 1;
	if (keycode == XK_e)
		open_door();
	if (keycode == XK_w)
		game()->player.moving_w = 1;
	if(keycode == XK_Right)
		game()->player.rot_r = 1;
	if(keycode == XK_Left)
		game()->player.rot_l = 1;
}

int	key_release(int keycode, t_game *nada)
{
	(void)nada;
	if(game()->state != GAME)
		return (0);
	if (keycode == XK_Shift_L)
		game()->player.diff = 0;
	if (keycode == XK_d)
		game()->player.moving_d = 0;
	if (keycode == XK_s)
		game()->player.moving_s = 0;
	if (keycode == XK_a)
		game()->player.moving_a = 0;
	if (keycode == XK_w)
		game()->player.moving_w = 0;
	if(keycode == XK_Right)
		game()->player.rot_r = 0;
	if(keycode == XK_Left)
		game()->player.rot_l = 0;
	return 0;
}
