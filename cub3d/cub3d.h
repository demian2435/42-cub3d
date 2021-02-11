
#ifndef CUB3D_H
#define CUB3D_H
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

#define R_LEFT 10
#define R_RIGHT 20
#define LEFT 30
#define RIGHT 40
#define UP 50
#define DOWN 60

typedef struct s_bmp
{
	unsigned int tot_size;
	unsigned short res1;
	unsigned short res2;
	unsigned int pixel_offset;
	unsigned int h_size;
	unsigned int w;
	unsigned int h;
	unsigned short planes;
	unsigned short bpp;
	unsigned int compression;
	unsigned int img_size;
	unsigned int xppm;
	unsigned int yppm;
	unsigned int tot_colors;
	unsigned int imp_colors;
} t_bmp;

typedef struct s_xy
{
	double x;
	double y;
	double _x;
	double _y;
	double dist;
} t_xy;

typedef struct s_img_data
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
	int width;
	int height;
} t_img_data;

typedef struct s_cub
{
	int res_x;
	int res_y;
	t_img_data txt_N;
	t_img_data txt_S;
	t_img_data txt_W;
	t_img_data txt_E;
	t_img_data txt_SPR;
	int n_sprites;
	t_list *sprites;
	int f_rgb[3];
	int c_rgb[3];
	char **map;
	int map_W;
	int map_H;
} t_cub;

typedef struct s_mlx_vars
{
	void *mlx;
	void *win;
} t_mlx_vars;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double speed;
	int move_y;
	int move_x;
	int move_r;
} t_player;

typedef struct s_system
{
	t_cub cub;
	t_img_data frame;
	t_mlx_vars mlx_vars;
	t_player player;
	int save;
} t_system;

void ft_print_pixel(int x, int y, int r, int g, int b, int a, t_system *sys);
int ft_key_exit(t_system *sys);

#endif