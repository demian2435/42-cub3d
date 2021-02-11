#include "cub3d.h"

int ft_next_frame(t_system *sys)
{
	sys->frame.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);
	sys->frame.addr = mlx_get_data_addr(sys->frame.img, &sys->frame.bpp, &sys->frame.line_len, &sys->frame.endian);
	sys->nf.x = 0;
	while (sys->nf.x < sys->cub.res_x)
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
		if (sys->nf.rayX < 0)
		{
			sys->nf.stepX = -1;
			sys->nf.sideX = (sys->player.pos_x - sys->nf.mapX) * sys->nf.deltaX;
		}
		else
		{
			sys->nf.stepX = 1;
			sys->nf.sideX = (sys->nf.mapX + 1.0 - sys->player.pos_x) * sys->nf.deltaX;
		}

		if (sys->nf.rayY < 0)
		{
			sys->nf.stepY = -1;
			sys->nf.sideY = (sys->player.pos_y - sys->nf.mapY) * sys->nf.deltaY;
		}
		else
		{
			sys->nf.stepY = 1;
			sys->nf.sideY = (sys->nf.mapY + 1.0 - sys->player.pos_y) * sys->nf.deltaY;
		}
		sys->nf.hit = 0;
		while (!sys->nf.hit)
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
			else if (sys->nf.mapX >= 0 && sys->nf.mapY >= 0 && sys->nf.mapX < sys->cub.map_W &&
					 sys->nf.mapY < sys->cub.map_H)
			{
				if (sys->cub.map[sys->nf.mapY][sys->nf.mapX] == '1')
					sys->nf.hit = 1;
			}
		}
		sys->nf.wallDist = 0;
		if (sys->nf.side == 0)
			sys->nf.wallDist = (sys->nf.mapX - sys->player.pos_x + (1 - sys->nf.stepX) / 2) / sys->nf.rayX;
		else if (sys->nf.side == 1)
			sys->nf.wallDist = (sys->nf.mapY - sys->player.pos_y + (1 - sys->nf.stepY) / 2) / sys->nf.rayY;
		sys->nf.line_h = (int)(sys->cub.res_y / sys->nf.wallDist);
		sys->nf.d_start = (int)(-sys->nf.line_h / 2 + sys->cub.res_y / 2);
		sys->nf.d_start = sys->nf.d_start < 0 ? 0 : sys->nf.d_start;
		sys->nf.d_start = sys->nf.d_start > sys->cub.res_y ? sys->cub.res_y : sys->nf.d_start;
		sys->nf.d_end = (sys->nf.line_h / 2 + sys->cub.res_y / 2);
		sys->nf.d_end = sys->nf.d_end > sys->cub.res_y ? sys->cub.res_y : sys->nf.d_end;
		sys->nf.d_end = sys->nf.d_end < 0 ? 0 : sys->nf.d_end;
		if (sys->nf.side == 0)
			sys->nf.wallX = sys->player.pos_y + sys->nf.wallDist * sys->nf.rayY;
		else
			sys->nf.wallX = sys->player.pos_x + sys->nf.wallDist * sys->nf.rayX;
		sys->nf.wallX -= (int)sys->nf.wallX;
		sys->nf.y = 0;
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
		while (sys->nf.sprite)
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
			if (sys->nf.x >= sys->nf.s_startX && sys->nf.x < sys->nf.s_endX &&
				sys->nf.transY > 0.1 && sys->nf.transY < sys->nf.wallDist)
			{
				sys->nf.texX = (int)(256 * (sys->nf.x - (-sys->nf.s_width / 2 + sys->nf.screenX)) * sys->cub.txt_SPR.width / sys->nf.s_width) / 256;
				while (sys->nf.s_startY < sys->nf.s_endY)
				{
					sys->nf.d = sys->nf.s_startY * 256 - sys->cub.res_y * 128 + sys->nf.s_height * 128;
					sys->nf.texY = ((sys->nf.d * sys->cub.txt_SPR.height) / sys->nf.s_height) / 256;
					sys->nf.col = (*(int *)(sys->cub.txt_SPR.addr + ((sys->nf.texY + (sys->nf.texX * sys->cub.txt_SPR.width)) * (sys->cub.txt_SPR.bpp / 8))));
					if ((unsigned int)sys->nf.col != 0x0000FF00)
						ft_print_pixel_exa(sys->nf.x, sys->nf.s_startY, sys->nf.col, sys);
					sys->nf.s_startY++;
				}
			}
			sys->nf.sprite = sys->nf.sprite->next;
		}
		sys->nf.x++;
	}
	/*MOVIMENTO PLAYER*/
	if (sys->player.move_r == R_LEFT)
	{
		double olddirx;
		double oldplanex;

		olddirx = sys->player.dir_x;
		sys->player.dir_x = (sys->player.dir_x * cos(-0.02)) - (sys->player.dir_y * sin(-0.02));
		sys->player.dir_y = (olddirx * sin(-0.02)) + (sys->player.dir_y * cos(-0.02));

		oldplanex = sys->player.plane_x;
		sys->player.plane_x = (sys->player.plane_x * cos(-0.02)) - (sys->player.plane_y * sin(-0.02));
		sys->player.plane_y = (oldplanex * sin(-0.02)) + (sys->player.plane_y * cos(-0.02));
	}
	else if (sys->player.move_r == R_RIGHT)
	{
		double olddirx;
		double oldplanex;

		olddirx = sys->player.dir_x;
		sys->player.dir_x = (sys->player.dir_x * cos(0.02)) - (sys->player.dir_y * sin(0.02));
		sys->player.dir_y = (olddirx * sin(0.02)) + (sys->player.dir_y * cos(0.02));

		oldplanex = sys->player.plane_x;
		sys->player.plane_x = (sys->player.plane_x * cos(0.02)) - (sys->player.plane_y * sin(0.02));
		sys->player.plane_y = (oldplanex * sin(0.02)) + (sys->player.plane_y * cos(0.02));
	}
	if (sys->player.move_x == LEFT)
	{
		double olddirx;
		double olddiry;
		double new_dir_x;
		double new_dir_y;
		double new_pos_x;
		double new_pos_y;

		olddirx = sys->player.dir_x;
		olddiry = sys->player.dir_y;
		new_dir_x = sys->player.dir_y;
		new_dir_y = -olddirx;
		new_pos_x = sys->player.pos_x + new_dir_x * sys->player.speed;
		new_pos_y = sys->player.pos_y + new_dir_y * sys->player.speed;
		new_dir_x = olddirx;
		new_dir_y = olddiry;

		if (sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '0')
		{
			sys->player.pos_x = new_pos_x;
			sys->player.pos_y = new_pos_y;
			sys->player.dir_x = new_dir_x;
			sys->player.dir_y = new_dir_y;
		}
	}
	else if (sys->player.move_x == RIGHT)
	{
		double olddirx;
		double olddiry;
		double new_dir_x;
		double new_dir_y;
		double new_pos_x;
		double new_pos_y;

		olddirx = sys->player.dir_x;
		olddiry = sys->player.dir_y;
		new_dir_x = -sys->player.dir_y;
		new_dir_y = olddirx;
		new_pos_x = sys->player.pos_x + new_dir_x * sys->player.speed;
		new_pos_y = sys->player.pos_y + new_dir_y * sys->player.speed;
		new_dir_x = olddirx;
		new_dir_y = olddiry;

		if (sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '0')
		{
			sys->player.pos_x = new_pos_x;
			sys->player.pos_y = new_pos_y;
			sys->player.dir_x = new_dir_x;
			sys->player.dir_y = new_dir_y;
		}
	}
	if (sys->player.move_y == UP)
	{
		double new_x = sys->player.pos_x + sys->player.dir_x * sys->player.speed;
		double new_y = sys->player.pos_y + sys->player.dir_y * sys->player.speed;
		if (sys->cub.map[(int)new_y][(int)new_x] == '0')
		{
			sys->player.pos_x = new_x;
			sys->player.pos_y = new_y;
		}
	}
	else if (sys->player.move_y == DOWN)
	{
		double new_x = sys->player.pos_x - sys->player.dir_x * sys->player.speed;
		double new_y = sys->player.pos_y - sys->player.dir_y * sys->player.speed;
		if (sys->cub.map[(int)new_y][(int)new_x] == '0')
		{
			sys->player.pos_x = new_x;
			sys->player.pos_y = new_y;
		}
	}
	if (sys->save == 0)
	{
		mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->frame.img, 0, 0);
		mlx_destroy_image(sys->mlx_vars.mlx, sys->frame.img);
	}
	return (0);
}