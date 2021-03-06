/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:23 by d2435             #+#    #+#             */
/*   Updated: 2021/02/14 10:33:58 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_press(int keycode, t_system *sys)
{
	if (keycode == 65307 || keycode == 53)
		ft_key_exit(sys);
	else if (keycode == 97 || keycode == 0)
		sys->player.move_x = LEFT;
	else if (keycode == 100 || keycode == 2)
		sys->player.move_x = RIGHT;
	else if (keycode == 119 || keycode == 13)
		sys->player.move_y = UP;
	else if (keycode == 115 || keycode == 1)
		sys->player.move_y = DOWN;
	else if (keycode == 65361 || keycode == 123)
		sys->player.move_r = R_LEFT;
	else if (keycode == 65363 || keycode == 124)
		sys->player.move_r = R_RIGHT;
	return (0);
}

int		ft_key_release(int keycode, t_system *sys)
{
	if ((keycode == 97 || keycode == 0) && sys->player.move_x == LEFT)
		sys->player.move_x = 0;
	else if ((keycode == 100 || keycode == 2) && sys->player.move_x == RIGHT)
		sys->player.move_x = 0;
	else if ((keycode == 119 || keycode == 13) && sys->player.move_y == UP)
		sys->player.move_y = 0;
	else if ((keycode == 115 || keycode == 1) && sys->player.move_y == DOWN)
		sys->player.move_y = 0;
	else if ((keycode == 65361 || keycode == 123) &&
		sys->player.move_r == R_LEFT)
		sys->player.move_r = 0;
	else if ((keycode == 65363 || keycode == 124) &&
		sys->player.move_r == R_RIGHT)
		sys->player.move_r = 0;
	return (0);
}

void	ft_clean_struct(t_system *sys)
{
	int i;

	if (sys->cub.map)
	{
		i = 0;
		while (sys->cub.map[i])
			free(sys->cub.map[i++]);
		free(sys->cub.map);
	}
	if (sys->cub.sprites)
	{
		ft_lstclear(&sys->cub.sprites, free);
		free(sys->cub.sprites);
	}
}

int		ft_key_exit(t_system *sys)
{
	if (sys->cub.txt_n.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_n.img);
	if (sys->cub.txt_s.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_s.img);
	if (sys->cub.txt_w.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_w.img);
	if (sys->cub.txt_e.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_e.img);
	if (sys->cub.txt_spr.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_spr.img);
	ft_clean_struct(sys);
	if (sys->mlx_vars.win)
		free(sys->mlx_vars.win);
	free(sys->mlx_vars.mlx);
	ft_printf("\n* * * * * * * * * * * * * *\n          by D2435");
	ft_printf("\n* * * * * * * * * * * * * *");
	ft_printf("\n Good bye my little friend\n* * * * * * * * * * * * * *\n");
	exit(0);
}
