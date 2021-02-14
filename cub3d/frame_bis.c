/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:32 by d2435             #+#    #+#             */
/*   Updated: 2021/02/14 10:46:57 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_frame_9(t_system *sys)
{
	if (sys->save == 0)
	{
		ft_rotate_left(sys);
		ft_rotate_right(sys);
		ft_move_left(sys);
		ft_move_right(sys);
		ft_move_up_down(sys);
		mlx_put_image_to_window(sys->mlx_vars.mlx,
			sys->mlx_vars.win, sys->frame.img, 0, 0);
		mlx_destroy_image(sys->mlx_vars.mlx, sys->frame.img);
	}
}

void	ft_frame_8(t_system *sys)
{
	if (sys->nf.x >= sys->nf.s_startx && sys->nf.x < sys->nf.s_endx &&
		sys->nf.transy > 0.1 && sys->nf.transy < sys->nf.walldist)
	{
		sys->nf.texx = (int)(256 * (sys->nf.x -
			(-sys->nf.s_width / 2 + sys->nf.screenx)) *
			sys->cub.txt_spr.width / sys->nf.s_width) / 256;
		while (sys->nf.s_starty < sys->nf.s_endy)
		{
			sys->nf.d = sys->nf.s_starty * 256 - sys->cub.res_y * 128 +
				sys->nf.s_height * 128;
			sys->nf.texy = ((sys->nf.d * sys->cub.txt_spr.height) /
				sys->nf.s_height) / 256;
			sys->nf.col = (*(int *)(sys->cub.txt_spr.addr +
				((sys->nf.texy + (sys->nf.texx * sys->cub.txt_spr.width)) *
				(sys->cub.txt_spr.bpp / 8))));
			if (sys->nf.col != 0x00FF00)
				ft_print_pixel_exa(sys->nf.x, sys->nf.s_starty,
					sys->nf.col, sys);
			sys->nf.s_starty++;
		}
	}
	sys->nf.sprite = sys->nf.sprite->next;
}

void	ft_frame_7(t_system *sys)
{
	sys->nf.sprx = ((t_xy *)(sys->nf.sprite->content))->x - sys->player.pos_x;
	sys->nf.spry = ((t_xy *)(sys->nf.sprite->content))->y - sys->player.pos_y;
	sys->nf.delta = 1.0 / (sys->player.plane_x *
		sys->player.dir_y - sys->player.dir_x * sys->player.plane_y);
	sys->nf.transx = sys->nf.delta * (sys->player.dir_y *
		sys->nf.sprx - sys->player.dir_x * sys->nf.spry);
	sys->nf.transy = sys->nf.delta * (-sys->player.plane_y *
		sys->nf.sprx + sys->player.plane_x * sys->nf.spry);
	sys->nf.screenx = (int)((sys->cub.res_x / 2) *
		(1 + sys->nf.transx / sys->nf.transy));
	sys->nf.s_width = abs((int)(sys->cub.res_y / sys->nf.transy));
	sys->nf.s_height = sys->nf.s_width;
	sys->nf.s_startx = -sys->nf.s_width / 2 + sys->nf.screenx;
	sys->nf.s_endx = sys->nf.s_width / 2 + sys->nf.screenx;
	sys->nf.s_starty = -sys->nf.s_height / 2 + sys->cub.res_y / 2;
	sys->nf.s_endy = sys->nf.s_height / 2 + sys->cub.res_y / 2;
	if (sys->nf.s_startx < 0)
		sys->nf.s_startx = 0;
	if (sys->nf.s_endx > sys->cub.res_x)
		sys->nf.s_endx = sys->cub.res_x;
	if (sys->nf.s_starty < 0)
		sys->nf.s_starty = 0;
	if (sys->nf.s_endy > sys->cub.res_y)
		sys->nf.s_endy = sys->cub.res_y;
}

void	ft_frame_6(t_system *sys)
{
	while (sys->nf.d_start <= sys->nf.d_end)
	{
		sys->nf.t_x = (int)fabs(sys->nf.tex_x);
		sys->nf.t_y = (int)fabs(sys->nf.tex_y);
		sys->nf.col = (*(int *)(sys->nf.texture.addr +
			(sys->nf.t_y + (sys->nf.t_x * sys->nf.texture.width)) *
			(sys->nf.texture.bpp / 8)));
		sys->nf.tex_y += sys->nf.wallstep;
		ft_print_pixel_exa(sys->nf.x, sys->nf.d_start++, sys->nf.col, sys);
	}
	sys->nf.sprite = sys->cub.sprites;
	ft_sprites_calc_dist(&sys->nf.sprite, sys);
	ft_sprites_sort(&sys->nf.sprite);
}

void	ft_frame_5(t_system *sys)
{
	while (sys->nf.y < sys->cub.res_y / 2)
	{
		sys->nf.col = ft_convert_color(sys->cub.c_rgb[0],
			sys->cub.c_rgb[1], sys->cub.c_rgb[2]);
		ft_print_pixel_exa(sys->nf.x, sys->nf.y++, sys->nf.col, sys);
	}
	while (sys->nf.y < sys->cub.res_y)
	{
		sys->nf.col = ft_convert_color(sys->cub.f_rgb[0],
			sys->cub.f_rgb[1], sys->cub.f_rgb[2]);
		ft_print_pixel_exa(sys->nf.x, sys->nf.y++, sys->nf.col, sys);
	}
	if (sys->nf.side == 0 && sys->nf.rayx < 0)
		sys->nf.texture = sys->cub.txt_w;
	else if (sys->nf.side == 0)
		sys->nf.texture = sys->cub.txt_e;
	else if (sys->nf.side == 1 && sys->nf.rayy < 0)
		sys->nf.texture = sys->cub.txt_n;
	else
		sys->nf.texture = sys->cub.txt_s;
	sys->nf.wallstep = 1.0 * sys->nf.texture.width / sys->nf.line_h;
	sys->nf.tex_y = (sys->nf.d_start - sys->cub.res_y / 2 +
		sys->nf.line_h / 2) * sys->nf.wallstep;
	sys->nf.tex_x = (int)(sys->nf.wallx * (double)sys->nf.texture.width);
	sys->nf.tex_x = sys->nf.texture.width - sys->nf.tex_x - 1;
}
