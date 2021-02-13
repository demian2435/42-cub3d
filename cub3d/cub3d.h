/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:39 by d2435             #+#    #+#             */
/*   Updated: 2021/02/13 13:50:27 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define R_LEFT 10
# define R_RIGHT 20
# define LEFT 30
# define RIGHT 40
# define UP 50
# define DOWN 60

# include <fcntl.h>
# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct		s_bmp
{
	unsigned int	tot_size;
	unsigned short	res1;
	unsigned short	res2;
	unsigned int	pixel_offset;
	unsigned int	h_size;
	unsigned int	w;
	unsigned int	h;
	unsigned short	planes;
	unsigned short	bpp;
	unsigned int	compression;
	unsigned int	img_size;
	unsigned int	xppm;
	unsigned int	yppm;
	unsigned int	tot_colors;
	unsigned int	imp_colors;
}					t_bmp;

typedef struct		s_xy
{
	double			x;
	double			y;
	double			t_x;
	double			t_y;
	double			dist;
}					t_xy;

typedef struct		s_img_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img_data;

typedef struct		s_next_frame
{
	int				x;
	int				y;
	int				t_x;
	int				t_y;
	double			delta;
	int				d;
	double			cam_x;
	double			rayx;
	double			rayy;
	int				mapx;
	int				mapy;
	double			deltax;
	double			deltay;
	int				stepx;
	int				stepy;
	int				side;
	double			sidex;
	double			sidey;
	int				hit;
	double			walldist;
	double			wallx;
	double			wallstep;
	int				line_h;
	int				d_start;
	int				d_end;
	t_img_data		texture;
	double			tex_y;
	double			tex_x;
	int				texx;
	int				texy;
	int				col;
	double			sprx;
	double			spry;
	double			transx;
	double			transy;
	int				screenx;
	t_list			*sprite;
	int				s_height;
	int				s_width;
	int				s_startx;
	int				s_endx;
	int				s_starty;
	int				s_endy;
}					t_next_frame;

typedef struct		s_cub
{
	int				res_x;
	int				res_y;
	t_img_data		txt_n;
	t_img_data		txt_s;
	t_img_data		txt_w;
	t_img_data		txt_e;
	t_img_data		txt_spr;
	int				n_sprites;
	t_list			*sprites;
	int				f_rgb[3];
	int				c_rgb[3];
	char			**map;
	int				map_w;
	int				map_h;
}					t_cub;

typedef struct		s_parse
{
	int				find;
	char			*line;
	char			*line_tmp;
	int				count;
	t_list			*list_map;
}					t_parse;

typedef struct		s_mlx_vars
{
	void			*mlx;
	void			*win;
}					t_mlx_vars;

typedef struct		s_player
{
	int				count;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	int				move_y;
	int				move_x;
	int				move_r;
	double			new_x;
	double			new_y;
}					t_player;

typedef struct		s_system
{
	t_cub			cub;
	t_img_data		frame;
	t_next_frame	nf;
	t_mlx_vars		mlx_vars;
	t_player		player;
	t_parse			parse;
	int				save;
	int				max_y;
	int				max_x;
}					t_system;

void				ft_exception(char *str, t_system *sys);
int					ft_isspacenear(char **map, int x, int y);
void				ft_init_player_dir(t_system *sys, char dir);
void				ft_set_player_start(t_system *sys, int x, int y);
void				ft_add_sprite(t_system *sys, int x, int y);
int					ft_control_map_bis(t_system *sys, int x, int y);
int					ft_control_map(t_system *sys);
void				ft_control_error_texture(t_system *sys);
void				ft_control_error_resolution(t_system *sys);
void				ft_control_errors(t_system *sys);
int					ft_isstartmap(char *str);
int					ft_ismap(char *str);
int					ft_mapmaxwidth(t_list *list_map);
void				ft_parse_cub(int fd, t_system *sys);
void				ft_print_pixel_exa(int x, int y, int color, t_system *sys);
int					ft_key_press(int keycode, t_system *sys);
int					ft_key_release(int keycode, t_system *sys);
void				ft_sprites_calc_dist(t_list **lst, t_system *sys);
void				ft_sprites_sort(t_list **lst);
void				ft_start_game(t_system *sys);
int					ft_istypefile(char *str, char *type, t_system *sys);
void				ft_write_on_file(t_system *sys, int fd, const void *buf,
						ssize_t len);
void				ft_init_bpm(t_system *sys, t_bmp *bmp);
void				ft_save_frame(t_system *sys);
int					main(int argc, char **argv);
void				ft_init_system(t_system *sys);
void				ft_start_save(char *str, t_system *sys);
int					ft_convert_color(int r, int g, int b);
void				ft_rotate_left(t_system *sys);
void				ft_rotate_right(t_system *sys);
void				ft_move_right(t_system *sys);
void				ft_move_left(t_system *sys);
void				ft_move_up_down(t_system *sys);
int					ft_next_frame(t_system *sys);
void				ft_frame_1(t_system *sys);
void				ft_frame_2(t_system *sys);
void				ft_frame_3(t_system *sys);
void				ft_frame_4(t_system *sys);
void				ft_frame_5(t_system *sys);
void				ft_frame_6(t_system *sys);
void				ft_frame_7(t_system *sys);
void				ft_frame_8(t_system *sys);
void				ft_frame_9(t_system *sys);
void				ft_clean_struct(t_system *sys);
int					ft_key_exit(t_system *sys);
void				ft_parse_resolution(t_system *sys);
void				ft_parse_map(int fd, t_system *sys);
void				ft_parse_texture_n(t_system *sys);
void				ft_parse_texture_s(t_system *sys);
void				ft_parse_texture_w(t_system *sys);
void				ft_parse_texture_e(t_system *sys);
void				ft_parse_floor(t_system *sys);
void				ft_parse_ceiling(t_system *sys);
int					ft_skip_spaces(t_system *sys);
void				ft_skip_digit(t_system *sys);
void				ft_parse_texture_spr(t_system *sys);
void				ft_parse_cub_bis(int fd, t_system *sys);
int					ft_isallspaces(char *str);

#endif
