#include "cub3d.h"

void ft_init_player_dir(t_system *sys, char dir)
{
	if (dir == 'N')
	{
		sys->player.dir_y = -1;
		sys->player.plane_x = (((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (dir == 'S')
	{
		sys->player.dir_y = 1;
		sys->player.plane_x = -(((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (dir == 'E')
	{
		sys->player.dir_x = 1;
		sys->player.plane_y = (((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (dir == 'W')
	{
		sys->player.dir_x = -1;
		sys->player.plane_y = -(((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
}

void ft_set_player_start(t_system *sys, int x, int y)
{
	ft_init_player_dir(sys, sys->cub.map[y][x]);
	if (!(sys->player.dir_x) && !(sys->player.plane_x))
		sys->player.plane_x = 0.5 * sys->player.dir_y;
	if (!(sys->player.dir_y) && !(sys->player.plane_y))
		sys->player.plane_y = 0.5 * sys->player.dir_x;
	if (sys->player.plane_x > 0)
		sys->player.plane_x = (sys->player.plane_x < 0.5 ? 1 - sys->player.plane_x : sys->player.plane_x);
	if (sys->player.plane_y > 0)
		sys->player.plane_y = (sys->player.plane_y < 0.5 ? 1 - sys->player.plane_y : sys->player.plane_y);
	sys->cub.map[y][x] = '0';
	sys->player.pos_x = 0.5 + x;
	sys->player.pos_y = 0.5 + y;
	sys->player.speed = 0.04;
	sys->player.count += 1;
}