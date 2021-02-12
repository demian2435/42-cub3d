/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:28 by d2435             #+#    #+#             */
/*   Updated: 2021/02/12 23:27:28 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_frame_4(t_system *sys)
{
	sys->nf.wallDist = 0;
	if (sys->nf.side == 0)
		sys->nf.wallDist = (sys->nf.mapX - sys->player.pos_x +
			(1 - sys->nf.stepX) / 2) / sys->nf.rayX;
	else if (sys->nf.side == 1)
		sys->nf.wallDist = (sys->nf.mapY - sys->player.pos_y +
			(1 - sys->nf.stepY) / 2) / sys->nf.rayY;
	sys->nf.line_h = (int)(sys->cub.res_y / sys->nf.wallDist);
	sys->nf.d_start = (int)(-sys->nf.line_h / 2 + sys->cub.res_y / 2);
	sys->nf.d_start = sys->nf.d_start < 0 ? 0 : sys->nf.d_start;
	sys->nf.d_start = sys->nf.d_start > sys->cub.res_y ?
		sys->cub.res_y : sys->nf.d_start;
	sys->nf.d_end = (sys->nf.line_h / 2 + sys->cub.res_y / 2);
	sys->nf.d_end = sys->nf.d_end > sys->cub.res_y ?
		sys->cub.res_y : sys->nf.d_end;
	sys->nf.d_end = sys->nf.d_end < 0 ? 0 : sys->nf.d_end;
	if (sys->nf.side == 0)
		sys->nf.wallX = sys->player.pos_y + sys->nf.wallDist * sys->nf.rayY;
	else
		sys->nf.wallX = sys->player.pos_x + sys->nf.wallDist * sys->nf.rayX;
	sys->nf.wallX -= (int)sys->nf.wallX;
	sys->nf.y = 0;
}

void	ft_frame_3(t_system *sys)
{
	if (sys->nf.sideX < sys->nf.sideY)
	{
		sys->nf.sideX += sys->nf.deltaX;
		sys->nf.mapX += sys->nf.stepX;
		sys->nf.side = 0;
	}
	else
	{
		sys->nf.sideY += sys->nf.deltaY;
		sys->nf.mapY += sys->nf.stepY;
		sys->nf.side = 1;
	}
	if (((sys->nf.mapX < 0 && sys->nf.stepX < 0) ||
		(sys->nf.mapY < 0 && sys->nf.stepY < 0) ||
		((sys->nf.mapX >= sys->cub.map_W) && sys->nf.stepX >= 0) ||
		((sys->nf.mapY >= sys->cub.map_H) && sys->nf.stepY >= 0)))
		sys->nf.hit = 1;
	else if (sys->nf.mapX >= 0 && sys->nf.mapY >= 0 &&
		sys->nf.mapX < sys->cub.map_W &&
		sys->nf.mapY < sys->cub.map_H)
	{
		if (sys->cub.map[sys->nf.mapY][sys->nf.mapX] == '1')
			sys->nf.hit = 1;
	}
}

void	ft_frame_2(t_system *sys)
{
	if (sys->nf.rayX < 0)
	{
		sys->nf.stepX = -1;
		sys->nf.sideX = (sys->player.pos_x - sys->nf.mapX) * sys->nf.deltaX;
	}
	else
	{
		sys->nf.stepX = 1;
		sys->nf.sideX = (sys->nf.mapX + 1.0 - sys->player.pos_x) *
			sys->nf.deltaX;
	}
	if (sys->nf.rayY < 0)
	{
		sys->nf.stepY = -1;
		sys->nf.sideY = (sys->player.pos_y - sys->nf.mapY) * sys->nf.deltaY;
	}
	else
	{
		sys->nf.stepY = 1;
		sys->nf.sideY = (sys->nf.mapY + 1.0 - sys->player.pos_y) *
			sys->nf.deltaY;
	}
	sys->nf.hit = 0;
}

void	ft_frame_1(t_system *sys)
{
	sys->nf.cameraX = 2 * sys->nf.x / (double)sys->cub.res_x - 1;
	sys->nf.rayX = sys->player.dir_x + sys->player.plane_x * sys->nf.cameraX;
	sys->nf.rayY = sys->player.dir_y + sys->player.plane_y * sys->nf.cameraX;
	if (sys->player.pos_x < 0)
		sys->nf.mapX = (-1) + (int)sys->player.pos_x;
	else
		sys->nf.mapX = (int)sys->player.pos_x;
	if (sys->player.pos_y < 0)
		sys->nf.mapY = (-1) + (int)sys->player.pos_y;
	else
		sys->nf.mapY = (int)sys->player.pos_y;
	sys->nf.deltaX = fabs(1 / sys->nf.rayX);
	sys->nf.deltaY = fabs(1 / sys->nf.rayY);
}

int		ft_next_frame(t_system *sys)
{
	sys->frame.img = mlx_new_image(sys->mlx_vars.mlx,
		sys->cub.res_x, sys->cub.res_y);
	sys->frame.addr = mlx_get_data_addr(sys->frame.img,
		&sys->frame.bpp, &sys->frame.line_len, &sys->frame.endian);
	sys->nf.x = 0;
	while (sys->nf.x < sys->cub.res_x)
	{
		ft_frame_1(sys);
		ft_frame_2(sys);
		while (!sys->nf.hit)
			ft_frame_3(sys);
		ft_frame_4(sys);
		ft_frame_5(sys);
		ft_frame_6(sys);
		while (sys->nf.sprite)
		{
			ft_frame_7(sys);
			ft_frame_8(sys);
		}
		sys->nf.x++;
	}
	ft_frame_9(sys);
	return (0);
}
