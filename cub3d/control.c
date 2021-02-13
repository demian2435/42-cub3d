/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:44 by d2435             #+#    #+#             */
/*   Updated: 2021/02/13 10:14:09 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_control_map_bis(t_system *sys, int x, int y)
{
	if (x == 0 || y == 0 || y == sys->cub.map_h - 1 || x == sys->cub.map_w - 1)
		return (0);
	if (ft_isspacenear(sys->cub.map, x, y))
		return (0);
	if (ft_isalpha(sys->cub.map[y][x]))
		ft_set_player_start(sys, x, y);
	if (sys->cub.map[y][x] == '2')
		ft_add_sprite(sys, x, y);
	return (1);
}

int		ft_control_map(t_system *sys)
{
	int x;
	int y;

	y = 0;
	while (y < sys->cub.map_h)
	{
		x = 0;
		while (x < sys->cub.map_w)
		{
			if (sys->cub.map[y][x] == '0' || sys->cub.map[y][x] == '2' ||
				sys->cub.map[y][x] == 'W' || sys->cub.map[y][x] == 'N' ||
				sys->cub.map[y][x] == 'S' || sys->cub.map[y][x] == 'E')
				if (ft_control_map_bis(sys, x, y) == 0)
					return (0);
			x++;
		}
		y++;
	}
	if (sys->player.count > 1)
		return (-2);
	else if (sys->player.count == 0)
		return (-1);
	return (1);
}

void	ft_control_error_texture(t_system *sys)
{
	if (sys->cub.txt_n.img == NULL)
		ft_exception("North texture NULL", sys);
	sys->cub.txt_n.addr = mlx_get_data_addr(sys->cub.txt_n.img,
		&sys->cub.txt_n.bpp, &sys->cub.txt_n.line_len, &sys->cub.txt_n.endian);
	if (sys->cub.txt_s.img == NULL)
		ft_exception("South texture NULL", sys);
	sys->cub.txt_s.addr = mlx_get_data_addr(sys->cub.txt_s.img,
		&sys->cub.txt_s.bpp, &sys->cub.txt_s.line_len, &sys->cub.txt_s.endian);
	if (sys->cub.txt_w.img == NULL)
		ft_exception("West texture NULL", sys);
	sys->cub.txt_w.addr = mlx_get_data_addr(sys->cub.txt_w.img,
		&sys->cub.txt_w.bpp, &sys->cub.txt_w.line_len, &sys->cub.txt_w.endian);
	if (sys->cub.txt_e.img == NULL)
		ft_exception("East texture NULL", sys);
	sys->cub.txt_e.addr = mlx_get_data_addr(sys->cub.txt_e.img,
		&sys->cub.txt_e.bpp, &sys->cub.txt_e.line_len, &sys->cub.txt_e.endian);
	if (sys->cub.txt_spr.img == NULL)
		ft_exception("Sprite texture NULL", sys);
	sys->cub.txt_spr.addr = mlx_get_data_addr(sys->cub.txt_spr.img,
		&sys->cub.txt_spr.bpp, &sys->cub.txt_spr.line_len,
		&sys->cub.txt_spr.endian);
}

void	ft_control_error_resolution(t_system *sys)
{
	if (sys->cub.res_x <= 0)
		ft_exception("Resolution X not valid", sys);
	if (sys->cub.res_x > sys->max_x)
	{
		ft_printf("Resize X resolution to %d\n", sys->max_x);
		sys->cub.res_x = sys->max_x;
	}
	if (sys->cub.res_y <= 0)
		ft_exception("Resolution Y not valid", sys);
	if (sys->cub.res_y > sys->max_y)
	{
		ft_printf("Resize Y resolution to %d\n", sys->max_y);
		sys->cub.res_y = sys->max_y;
	}
}

void	ft_control_errors(t_system *sys)
{
	int ret;

	ft_control_error_resolution(sys);
	ft_control_error_texture(sys);
	if (sys->cub.f_rgb[0] < 0 || sys->cub.f_rgb[0] > 255 ||
		sys->cub.f_rgb[1] < 0 || sys->cub.f_rgb[1] > 255 ||
		sys->cub.f_rgb[2] < 0 || sys->cub.f_rgb[2] > 255)
		ft_exception("Floor color values", sys);
	if (sys->cub.c_rgb[0] < 0 || sys->cub.c_rgb[0] > 255 ||
		sys->cub.c_rgb[1] < 0 || sys->cub.c_rgb[1] > 255 ||
		sys->cub.c_rgb[2] < 0 || sys->cub.c_rgb[2] > 255)
		ft_exception("Ceiling color values", sys);
	if (sys->cub.map_w < 3)
		ft_exception("Map width too small", sys);
	if (sys->cub.map_h < 3)
		ft_exception("Map height too small", sys);
	ret = ft_control_map(sys);
	if (ret == 0)
		ft_exception("Map border open", sys);
	else if (ret == -2)
		ft_exception("Multyplayer not allowed", sys);
	else if (ret == -1)
		ft_exception("No player spawn point", sys);
}
