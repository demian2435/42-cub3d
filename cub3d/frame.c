/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:28 by d2435             #+#    #+#             */
/*   Updated: 2021/02/14 10:51:49 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_frame_4(t_system *sys)
{
	sys->nf.walldist = 0;
	if (sys->nf.side == 0)
		sys->nf.walldist = (sys->nf.mapx - sys->player.pos_x +
			(1 - sys->nf.stepx) / 2) / sys->nf.rayx;
	else if (sys->nf.side == 1)
		sys->nf.walldist = (sys->nf.mapy - sys->player.pos_y +
			(1 - sys->nf.stepy) / 2) / sys->nf.rayy;
	sys->nf.line_h = (int)(sys->cub.res_y / sys->nf.walldist);
	sys->nf.d_start = (int)(-sys->nf.line_h / 2 + sys->cub.res_y / 2);
	sys->nf.d_start = sys->nf.d_start < 0 ? 0 : sys->nf.d_start;
	sys->nf.d_start = sys->nf.d_start > sys->cub.res_y ?
		sys->cub.res_y : sys->nf.d_start;
	sys->nf.d_end = (sys->nf.line_h / 2 + sys->cub.res_y / 2);
	sys->nf.d_end = sys->nf.d_end > sys->cub.res_y ?
		sys->cub.res_y : sys->nf.d_end;
	sys->nf.d_end = sys->nf.d_end < 0 ? 0 : sys->nf.d_end;
	if (sys->nf.side == 0)
		sys->nf.wallx = sys->player.pos_y + sys->nf.walldist * sys->nf.rayy;
	else
		sys->nf.wallx = sys->player.pos_x + sys->nf.walldist * sys->nf.rayx;
	sys->nf.wallx -= (int)sys->nf.wallx;
	sys->nf.y = 0;
}

void	ft_frame_3(t_system *sys)
{
	if (sys->nf.sidex < sys->nf.sidey)
	{
		sys->nf.sidex += sys->nf.deltax;
		sys->nf.mapx += sys->nf.stepx;
		sys->nf.side = 0;
	}
	else
	{
		sys->nf.sidey += sys->nf.deltay;
		sys->nf.mapy += sys->nf.stepy;
		sys->nf.side = 1;
	}
	if (((sys->nf.mapx < 0 && sys->nf.stepx < 0) ||
		(sys->nf.mapy < 0 && sys->nf.stepy < 0) ||
		((sys->nf.mapx >= sys->cub.map_w) && sys->nf.stepx >= 0) ||
		((sys->nf.mapy >= sys->cub.map_h) && sys->nf.stepy >= 0)))
		sys->nf.hit = 1;
	else if (sys->nf.mapx >= 0 && sys->nf.mapy >= 0 &&
		sys->nf.mapx < sys->cub.map_w &&
		sys->nf.mapy < sys->cub.map_h)
	{
		if (sys->cub.map[sys->nf.mapy][sys->nf.mapx] == '1')
			sys->nf.hit = 1;
	}
}

void	ft_frame_2(t_system *sys)
{
	if (sys->nf.rayx < 0)
	{
		sys->nf.stepx = -1;
		sys->nf.sidex = (sys->player.pos_x - sys->nf.mapx) * sys->nf.deltax;
	}
	else
	{
		sys->nf.stepx = 1;
		sys->nf.sidex = (sys->nf.mapx + 1.0 - sys->player.pos_x) *
			sys->nf.deltax;
	}
	if (sys->nf.rayy < 0)
	{
		sys->nf.stepy = -1;
		sys->nf.sidey = (sys->player.pos_y - sys->nf.mapy) * sys->nf.deltay;
	}
	else
	{
		sys->nf.stepy = 1;
		sys->nf.sidey = (sys->nf.mapy + 1.0 - sys->player.pos_y) *
			sys->nf.deltay;
	}
	sys->nf.hit = 0;
}

void	ft_frame_1(t_system *sys)
{
	sys->nf.cam_x = 2 * sys->nf.x / (double)sys->cub.res_x - 1;
	sys->nf.rayx = sys->player.dir_x + sys->player.plane_x * sys->nf.cam_x;
	sys->nf.rayy = sys->player.dir_y + sys->player.plane_y * sys->nf.cam_x;
	if (sys->player.pos_x < 0)
		sys->nf.mapx = (-1) + (int)sys->player.pos_x;
	else
		sys->nf.mapx = (int)sys->player.pos_x;
	if (sys->player.pos_y < 0)
		sys->nf.mapy = (-1) + (int)sys->player.pos_y;
	else
		sys->nf.mapy = (int)sys->player.pos_y;
	sys->nf.deltax = fabs(1 / sys->nf.rayx);
	sys->nf.deltay = fabs(1 / sys->nf.rayy);
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
