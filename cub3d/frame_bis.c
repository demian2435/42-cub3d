#include "cub3d.h"

void ft_frame_9(t_system *sys)
{
	ft_rotate_left(sys);
	ft_rotate_right(sys);
	ft_move_left(sys);
	ft_move_right(sys);
	ft_move_up_down(sys);
	if (sys->save == 0)
	{
		mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->frame.img, 0, 0);
		mlx_destroy_image(sys->mlx_vars.mlx, sys->frame.img);
	}
}

void ft_frame_8(t_system *sys)
{
	if (sys->nf.x >= sys->nf.s_startX && sys->nf.x < sys->nf.s_endX &&
		sys->nf.transY > 0.1 && sys->nf.transY < sys->nf.wallDist)
	{
		sys->nf.texX = (int)(256 * (sys->nf.x - (-sys->nf.s_width / 2 + sys->nf.screenX)) * sys->cub.txt_SPR.width / sys->nf.s_width) / 256;
		while (sys->nf.s_startY < sys->nf.s_endY)
		{
			sys->nf.d = sys->nf.s_startY * 256 - sys->cub.res_y * 128 + sys->nf.s_height * 128;
			sys->nf.texY = ((sys->nf.d * sys->cub.txt_SPR.height) / sys->nf.s_height) / 256;
			sys->nf.col = (*(int *)(sys->cub.txt_SPR.addr + ((sys->nf.texY + (sys->nf.texX * sys->cub.txt_SPR.width)) * (sys->cub.txt_SPR.bpp / 8))));
			if ((unsigned int)sys->nf.col != 4278255360)
				ft_print_pixel_exa(sys->nf.x, sys->nf.s_startY, sys->nf.col, sys);
			sys->nf.s_startY++;
		}
	}
	sys->nf.sprite = sys->nf.sprite->next;
}

void ft_frame_7(t_system *sys)
{
	sys->nf.sprX = ((t_xy *)(sys->nf.sprite->content))->x - sys->player.pos_x;
	sys->nf.sprY = ((t_xy *)(sys->nf.sprite->content))->y - sys->player.pos_y;
	sys->nf.delta = 1.0 / (sys->player.plane_x * sys->player.dir_y - sys->player.dir_x * sys->player.plane_y);
	sys->nf.transX = sys->nf.delta * (sys->player.dir_y * sys->nf.sprX - sys->player.dir_x * sys->nf.sprY);
	sys->nf.transY = sys->nf.delta * (-sys->player.plane_y * sys->nf.sprX + sys->player.plane_x * sys->nf.sprY);
	sys->nf.screenX = (int)((sys->cub.res_x / 2) * (1 + sys->nf.transX / sys->nf.transY));
	sys->nf.s_width = abs((int)(sys->cub.res_y / sys->nf.transY));
	sys->nf.s_height = sys->nf.s_width;
	sys->nf.s_startX = -sys->nf.s_width / 2 + sys->nf.screenX;
	sys->nf.s_endX = sys->nf.s_width / 2 + sys->nf.screenX;
	sys->nf.s_startY = -sys->nf.s_height / 2 + sys->cub.res_y / 2;
	sys->nf.s_endY = sys->nf.s_height / 2 + sys->cub.res_y / 2;
	if (sys->nf.s_startX < 0)
		sys->nf.s_startX = 0;
	if (sys->nf.s_endX > sys->cub.res_x)
		sys->nf.s_endX = sys->cub.res_x;
	if (sys->nf.s_startY < 0)
		sys->nf.s_startY = 0;
	if (sys->nf.s_endY > sys->cub.res_y)
		sys->nf.s_endY = sys->cub.res_y;
}

void ft_frame_6(t_system *sys)
{
	while (sys->nf.d_start <= sys->nf.d_end)
	{
		sys->nf._x = (int)fabs(sys->nf.tex_x);
		sys->nf._y = (int)fabs(sys->nf.tex_y);
		sys->nf.col = (*(int *)(sys->nf.texture.addr + (sys->nf._y + (sys->nf._x * sys->nf.texture.width)) * (sys->nf.texture.bpp / 8)));
		sys->nf.tex_y += sys->nf.wallStep;
		ft_print_pixel_exa(sys->nf.x, sys->nf.d_start++, sys->nf.col, sys);
	}
	sys->nf.sprite = sys->cub.sprites;
	ft_sprites_calc_dist(&sys->nf.sprite, sys);
	ft_sprites_sort(&sys->nf.sprite);
}

void ft_frame_5(t_system *sys)
{
	while (sys->nf.y < sys->cub.res_y / 2)
	{
		sys->nf.col = ft_convert_color(sys->cub.c_rgb[0], sys->cub.c_rgb[1], sys->cub.c_rgb[2]);
		ft_print_pixel_exa(sys->nf.x, sys->nf.y, sys->nf.col, sys);
		sys->nf.y++;
	}
	while (sys->nf.y < sys->cub.res_y)
	{
		sys->nf.col = ft_convert_color(sys->cub.f_rgb[0], sys->cub.f_rgb[1], sys->cub.f_rgb[2]);
		ft_print_pixel_exa(sys->nf.x, sys->nf.y, sys->nf.col, sys);
		sys->nf.y++;
	}
	if (sys->nf.side == 0 && sys->nf.rayX < 0)
		sys->nf.texture = sys->cub.txt_E;
	else if (sys->nf.side == 0)
		sys->nf.texture = sys->cub.txt_W;
	else if (sys->nf.side == 1 && sys->nf.rayY < 0)
		sys->nf.texture = sys->cub.txt_S;
	else
		sys->nf.texture = sys->cub.txt_N;
	sys->nf.wallStep = 1.0 * sys->nf.texture.width / sys->nf.line_h;
	sys->nf.tex_y = (sys->nf.d_start - sys->cub.res_y / 2 + sys->nf.line_h / 2) * sys->nf.wallStep;
	sys->nf.tex_x = (int)(sys->nf.wallX * (double)sys->nf.texture.width);
	sys->nf.tex_x = sys->nf.texture.width - sys->nf.tex_x - 1;
}