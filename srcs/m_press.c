/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_press.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicosta- <dicosta-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:43:00 by rmota-ma          #+#    #+#             */
/*   Updated: 2025/10/30 23:06:55 by dicosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mouse_press(int keycode, void *nada)
{
	(void)nada;

	if(keycode != 1)
		return (0);
	game()->release++;
	if(game()->release > 1)
		game()->release = 0;
	if(game()->release)
		return (0);
	else if(game()->state == MENU)
		main_press();
	else if(game()->state == OPT_M)
		opt_m_press();
	else if(game()->state == CTRL_M)
		ctrl_m_press();
	else if(game()->state == PAUSE)
		pause_press();
	else if(game()->state == OPT_P)
		opt_p_press();
	else if(game()->state == CTRL_P)
		ctrl_p_press();
	//printf("mouse x: %d, mouse y: %d, menued: %d, keycode: %d\n", mx, my, game()->state == MENU, keycode);
	return (0);
}

void	main_press(void)
{
	int	mx;
	int	my;

	mx = 0;
	my = 0;
	mlx_mouse_get_pos(game()->mlx, game()->win, &mx, &my);
	if((game()->mouse.x >= 672 && game()->mouse.x <= 1248) && (game()->mouse.y >= 500 && game()->mouse.y <= 616))//trocar cordenadas de acordo com botoes
	{
		mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
		mlx_mouse_move(game()->mlx, game()->win, game()->mouse.x, 1070);
		mx = game()->mouse.x;
		set_difficulty();
		game_move(&mx);
		darken(game()->st_anim[game()->frame.anim_tg], 1.0, -0.05);
		game()->frame.play_tg = 0;
		lighten(game()->canvas, 0.0);
		game()->state = GAME;
	}
	else if((game()->mouse.x >= 672 && game()->mouse.x <= 1248) && (game()->mouse.y >= 666 && game()->mouse.y <= 782))
	{
		opt_m_move();
		game()->state = OPT_M;
	}
	else if((game()->mouse.x >= 672 && game()->mouse.x <= 1248) && (game()->mouse.y >= 832 && game()->mouse.y <= 948))//trocar cordenadas de acordo com botoes
		clean_exit(NULL);
}

void	opt_m_press(void)
{
	t_cord	pos;
	mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
	pos.x = game()->mouse.x;
	pos.y = game()->mouse.y;
	if ((game()->mouse.x >= 532 && game()->mouse.x <= 1387) && (game()->mouse.y >= 663 && game()->mouse.y <= 743))
	{
		ctrl_m_move();
		game()->state = CTRL_M;
	}
	if ((game()->mouse.x >= 532 && game()->mouse.x <= 1387) && (game()->mouse.y >= 764 && game()->mouse.y <= 843))
	{
		main_move();
		game()->state = MENU;
	}
	if(find_point(pos, game()->sleft_c[0], game()->sleft_c[1], game()->sleft_c[2]))
		if(game()->frame.sens_tg != 0)
			game()->frame.sens_tg--;
	if(find_point(pos, game()->sright_c[0], game()->sright_c[1], game()->sright_c[2]))
		if(game()->frame.sens_tg != 4)
			game()->frame.sens_tg++;
	if(find_point(pos, game()->dleft_c[0], game()->dleft_c[1], game()->dleft_c[2]))
		if(game()->frame.diff_tg != 0)
			game()->frame.diff_tg--;
	if(find_point(pos, game()->dright_c[0], game()->dright_c[1], game()->dright_c[2]))
		if(game()->frame.diff_tg != 2)
			game()->frame.diff_tg++;
}

void	ctrl_m_press(void)
{
	mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
	if((game()->mouse.x >= 362 && game()->mouse.x <= 1556) && (game()->mouse.y >= 914 && game()->mouse.y <= 992))
	{
		opt_m_move();
		game()->state = OPT_M;
	}
}

void	pause_press(void)
{
	int last_x;
	mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
		if((game()->mouse.x >= 754 && game()->mouse.x <= 1164) && (game()->mouse.y >= 463 && game()->mouse.y <= 542))
	{
		mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
		mlx_mouse_move(game()->mlx, game()->win, game()->mouse.x, 1070);
		last_x = game()->mouse.x;
		game_move(&last_x);
		game()->state = GAME;
		lighten(game()->canvas, 0.4);
	}
	if((game()->mouse.x >= 754 && game()->mouse.x <= 1164) && (game()->mouse.y >= 563 && game()->mouse.y <= 641))
	{
		opt_p_move();
		game()->state = OPT_P;
	}
	if((game()->mouse.x >= 754 && game()->mouse.x <= 1164) && (game()->mouse.y >= 664 && game()->mouse.y <= 743))
	{
		darken(game()->canvas, 0.4, -0.05);
		lighten(game()->st_anim[game()->frame.anim_tg], 0.0);
		main_move();
		reset_map();
		reinit();
		game()->state = MENU;
	}
	if((game()->mouse.x >= 754 && game()->mouse.x <= 1164) && (game()->mouse.y >= 764 && game()->mouse.y <= 843))
		clean_exit(NULL);
}

void	opt_p_press(void)
{
	t_cord	pos;
	mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
	pos.x = game()->mouse.x;
	pos.y = game()->mouse.y;
	if((game()->mouse.x >= 531 && game()->mouse.x <= 1389) && (game()->mouse.y >= 612 && game()->mouse.y <= 692))
	{
		ctrl_p_move();
		game()->state = CTRL_P;
	}
	if((game()->mouse.x >= 532 && game()->mouse.x <= 1390) && (game()->mouse.y >= 713 && game()->mouse.y <= 793))
	{
		pause_move();
		game()->state = PAUSE;
	}
	if(find_point(pos, game()->sleft_pause_c[0], game()->sleft_pause_c[1], game()->sleft_pause_c[2]))
		if(game()->frame.sens_tg != 0)
			game()->frame.sens_tg--;
	if(find_point(pos, game()->sright_pause_c[0], game()->sright_pause_c[1], game()->sright_pause_c[2]))
		if(game()->frame.sens_tg != 4)
			game()->frame.sens_tg++;
}

void	ctrl_p_press(void)
{
	mlx_mouse_get_pos(game()->mlx, game()->win, &game()->mouse.x, &game()->mouse.y);
	if((game()->mouse.x >= 362 && game()->mouse.x <= 1556) && (game()->mouse.y >= 914 && game()->mouse.y <= 992))
	{
		opt_p_move();
		game()->state = OPT_P;
	}
}

int	pause_game(void)
{
	pause_move();
	darken(game()->canvas, 1.0, 0.40);
	game()->state = PAUSE;
	game()->player.moving_w = 0;
	game()->player.moving_a = 0;
	game()->player.moving_s = 0;
	game()->player.moving_d = 0;
	game()->player.rot_r = 0;
	game()->player.rot_l = 0;
	return (0);
}
