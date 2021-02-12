#include "cub3d.h"

void ft_rotate_left(t_system *sys)
{
	double olddirx;
	double oldplanex;

	if (sys->player.move_r != R_LEFT)
		return;
	olddirx = sys->player.dir_x;
	sys->player.dir_x = (sys->player.dir_x * cos(-0.02)) - (sys->player.dir_y * sin(-0.02));
	sys->player.dir_y = (olddirx * sin(-0.02)) + (sys->player.dir_y * cos(-0.02));
	oldplanex = sys->player.plane_x;
	sys->player.plane_x = (sys->player.plane_x * cos(-0.02)) - (sys->player.plane_y * sin(-0.02));
	sys->player.plane_y = (oldplanex * sin(-0.02)) + (sys->player.plane_y * cos(-0.02));
}

void ft_rotate_right(t_system *sys)
{
	double olddirx;
	double oldplanex;

	if (sys->player.move_r != R_RIGHT)
		return;
	olddirx = sys->player.dir_x;
	sys->player.dir_x = (sys->player.dir_x * cos(0.02)) - (sys->player.dir_y * sin(0.02));
	sys->player.dir_y = (olddirx * sin(0.02)) + (sys->player.dir_y * cos(0.02));
	oldplanex = sys->player.plane_x;
	sys->player.plane_x = (sys->player.plane_x * cos(0.02)) - (sys->player.plane_y * sin(0.02));
	sys->player.plane_y = (oldplanex * sin(0.02)) + (sys->player.plane_y * cos(0.02));
}

void ft_move_left(t_system *sys)
{
	double olddirx;
	double olddiry;
	double new_dir_x;
	double new_dir_y;

	if (sys->player.move_x != LEFT)
		return;
	olddirx = sys->player.dir_x;
	olddiry = sys->player.dir_y;
	new_dir_x = sys->player.dir_y;
	new_dir_y = -olddirx;
	sys->player.new_x = sys->player.pos_x + new_dir_x * sys->player.speed;
	sys->player.new_y = sys->player.pos_y + new_dir_y * sys->player.speed;
	new_dir_x = olddirx;
	new_dir_y = olddiry;
	if (sys->cub.map[(int)sys->player.new_y][(int)sys->player.new_x] == '0')
	{
		sys->player.pos_x = sys->player.new_x;
		sys->player.pos_y = sys->player.new_y;
		sys->player.dir_x = new_dir_x;
		sys->player.dir_y = new_dir_y;
	}
}

void ft_move_right(t_system *sys)
{
	double olddirx;
	double olddiry;
	double new_dir_x;
	double new_dir_y;

	if (sys->player.move_x != RIGHT)
		return;
	olddirx = sys->player.dir_x;
	olddiry = sys->player.dir_y;
	new_dir_x = -sys->player.dir_y;
	new_dir_y = olddirx;
	sys->player.new_x = sys->player.pos_x + new_dir_x * sys->player.speed;
	sys->player.new_y = sys->player.pos_y + new_dir_y * sys->player.speed;
	new_dir_x = olddirx;
	new_dir_y = olddiry;
	if (sys->cub.map[(int)sys->player.new_y][(int)sys->player.new_x] == '0')
	{
		sys->player.pos_x = sys->player.new_x;
		sys->player.pos_y = sys->player.new_y;
		sys->player.dir_x = new_dir_x;
		sys->player.dir_y = new_dir_y;
	}
}

void ft_move_up_down(t_system *sys)
{
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
}