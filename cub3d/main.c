/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:38:52 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/04 19:12:41 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void ft_exception(char *str, t_system *sys)
{
	ft_printf("Error\n%s\n", str);
	ft_key_exit(sys);
}

int ft_isSpaceNear(char **map, int x, int y)
{
	if (map[y][x + 1] == ' ')
		return (1);
	if (map[y][x - 1] == ' ')
		return (1);
	if (map[y + 1][x] == ' ')
		return (1);
	if (map[y - 1][x] == ' ')
		return (1);
	if (map[y + 1][x + 1] == ' ')
		return (1);
	if (map[y - 1][x + 1] == ' ')
		return (1);
	if (map[y + 1][x - 1] == ' ')
		return (1);
	if (map[y - 1][x - 1] == ' ')
		return (1);
	return (0);
}

void ft_set_player_start(t_system *sys, int x, int y)
{
	if (sys->cub.map[y][x] == 'N')
	{
		sys->player.dir_y = -1;
		sys->player.plane_x = (((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'S')
	{
		sys->player.dir_y = 1;
		sys->player.plane_x = -(((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'E')
	{
		sys->player.dir_x = 1;
		sys->player.plane_y = (((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'W')
	{
		sys->player.dir_x = -1;
		sys->player.plane_y = -(((double)sys->cub.res_x / (double)sys->cub.res_y) - 1.0);
	}
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
}

int ft_controlMap(t_system *sys)
{
	int x;
	int y;
	int count;

	count = 0;
	y = 0;
	while (y < sys->cub.map_H)
	{
		x = 0;
		while (x < sys->cub.map_W)
		{
			if (sys->cub.map[y][x] == '0' || sys->cub.map[y][x] == '2' || ft_isalpha(sys->cub.map[y][x]))
			{
				if (x == 0 || y == 0 || y == sys->cub.map_H - 1 || x == sys->cub.map_W - 1)
					return (0);
				if (ft_isSpaceNear(sys->cub.map, x, y))
					return (0);
				if (ft_isalpha(sys->cub.map[y][x]))
				{
					count++;
					ft_set_player_start(sys, x, y);
				}
				if (sys->cub.map[y][x] == '2')
				{
					t_xy *pos = malloc(sizeof(t_xy));
					pos->x = x + 0.5;
					pos->y = y + 0.5;
					ft_lstadd_front(&sys->cub.sprites, ft_lstnew(pos));
					sys->cub.map[y][x] = '0';
					sys->cub.n_sprites++;
				}
			}
			x++;
		}
		y++;
	}
	if (count > 1)
		return (-2);
	else if (count == 0)
		return (-1);
	return (1);
}

void ft_controlError(t_system *sys)
{
	int ret;

	if (sys->cub.res_x <= 0)
		ft_exception("Resolution X not valid", sys);
	if (sys->cub.res_x > 1920)
	{
		ft_printf("Resize X resolution to 1920");
		sys->cub.res_x = 1920;
	}
	if (sys->cub.res_y <= 0)
		ft_exception("Resolution Y not valid", sys);
	if (sys->cub.res_y > 1080)
	{
		ft_printf("Resize Y resolution to 1080");
		sys->cub.res_y = 1080;
	}
	if (sys->cub.txt_N.img == NULL)
		ft_exception("North texture NULL", sys);
	sys->cub.txt_N.addr = mlx_get_data_addr(sys->cub.txt_N.img, &sys->cub.txt_N.bpp, &sys->cub.txt_N.line_len, &sys->cub.txt_N.endian);
	if (sys->cub.txt_S.img == NULL)
		ft_exception("South texture NULL", sys);
	sys->cub.txt_S.addr = mlx_get_data_addr(sys->cub.txt_S.img, &sys->cub.txt_S.bpp, &sys->cub.txt_S.line_len, &sys->cub.txt_S.endian);
	if (sys->cub.txt_W.img == NULL)
		ft_exception("West texture NULL", sys);
	sys->cub.txt_W.addr = mlx_get_data_addr(sys->cub.txt_W.img, &sys->cub.txt_W.bpp, &sys->cub.txt_W.line_len, &sys->cub.txt_W.endian);
	if (sys->cub.txt_E.img == NULL)
		ft_exception("East texture NULL", sys);
	sys->cub.txt_E.addr = mlx_get_data_addr(sys->cub.txt_E.img, &sys->cub.txt_E.bpp, &sys->cub.txt_E.line_len, &sys->cub.txt_E.endian);
	if (sys->cub.txt_SPR.img == NULL)
		ft_exception("Sprite texture NULL", sys);
	sys->cub.txt_SPR.addr = mlx_get_data_addr(sys->cub.txt_SPR.img, &sys->cub.txt_SPR.bpp, &sys->cub.txt_SPR.line_len, &sys->cub.txt_SPR.endian);
	if (sys->cub.f_rgb[0] < 0 || sys->cub.f_rgb[0] > 255 ||
		sys->cub.f_rgb[1] < 0 || sys->cub.f_rgb[1] > 255 ||
		sys->cub.f_rgb[2] < 0 || sys->cub.f_rgb[2] > 255)
		ft_exception("Floor color values", sys);
	if (sys->cub.c_rgb[0] < 0 || sys->cub.c_rgb[0] > 255 ||
		sys->cub.c_rgb[1] < 0 || sys->cub.c_rgb[1] > 255 ||
		sys->cub.c_rgb[2] < 0 || sys->cub.c_rgb[2] > 255)
		ft_exception("Ceiling color values", sys);
	if (sys->cub.map_W < 3)
		ft_exception("Map width too small", sys);
	if (sys->cub.map_H < 3)
		ft_exception("Map height too small", sys);
	ret = ft_controlMap(sys);
	if (ret == 0)
		ft_exception("Map border open", sys);
	else if (ret == -2)
		ft_exception("Multyplayer not allowed", sys);
	else if (ret == -1)
		ft_exception("No player spawn point", sys);
}

int ft_isstartmap(char *str)
{
	int walls;

	walls = 0;
	while (*str)
	{
		if (*str == ' ')
			str++;
		else if (*str == '1')
		{
			walls++;
			str++;
		}
		else
			return (0);
	}
	if (walls > 0)
		return (1);
	return (0);
}

int ft_ismap(char *str)
{
	int walls;

	walls = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '0' || *str == '2' || *str == 'N' || *str == 'S' || *str == 'W' || *str == 'E')
			str++;
		else if (*str == '1')
		{
			walls++;
			str++;
		}
		else
			return (0);
	}
	if (walls > 0)
		return (1);
	return (0);
}

static void ft_parseFileCub_bis(int fd, t_system *sys, t_list **list_map)
{
	char *line;
	char *p_line;
	int count;

	count = 0;
	while ((count = ft_get_next_line(fd, &line)) > 0)
	{
		p_line = line;
		if (ft_isstartmap(line))
		{
			if (*list_map)
				ft_exception("Duplicated map", sys);
			*list_map = ft_lstnew(line);
			while ((count = ft_get_next_line(fd, &line)) > 0)
			{
				if (ft_ismap(line))
					ft_lstadd_back(&(*list_map), ft_lstnew(line));
				else
					break;
			}
			if (ft_ismap(line))
				ft_lstadd_back(&(*list_map), ft_lstnew(line));
			break;
		}
		else if (line[0] == 'R' && ft_isspace(line[1]))
		{
			if (sys->cub.res_x != -1 && sys->cub.res_y != -1)
				ft_exception("Duplicated resolution", sys);
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.res_x = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.res_y = ft_atoi(line);
		}
		else if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		{
			if (sys->cub.txt_N.img != NULL)
				ft_exception("Duplicated north texture", sys);
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_N.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_N.width, &sys->cub.txt_N.height);
		}
		else if (*line == 'S' && *(line + 1) == 'O' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_S.img != NULL)
				ft_exception("Duplicated south texture", sys);
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_S.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_S.width, &sys->cub.txt_S.height);
		}
		else if (*line == 'W' && *(line + 1) == 'E' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_W.img != NULL)
				ft_exception("Duplicated west texture", sys);
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_W.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_W.width, &sys->cub.txt_W.height);
		}
		else if (*line == 'E' && *(line + 1) == 'A' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_E.img != NULL)
				ft_exception("Duplicated east texture", sys);
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_E.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_E.width, &sys->cub.txt_E.height);
		}
		else if (*line == 'S' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.txt_SPR.img != NULL)
				ft_exception("Duplicated sprite texture", sys);
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_SPR.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_SPR.width, &sys->cub.txt_SPR.height);
		}
		else if (*line == 'F' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.f_rgb[0] != -1 && sys->cub.f_rgb[1] != -1 && sys->cub.f_rgb[2] != -1)
				ft_exception("Duplicated floor color", sys);
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing floor color", sys);
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[1] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing floor color", sys);
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[2] = ft_atoi(line);
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			if (sys->cub.c_rgb[0] != -1 && sys->cub.c_rgb[1] != -1 && sys->cub.c_rgb[2] != -1)
				ft_exception("Duplicated ceiling color", sys);
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing ceiling color", sys);
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[1] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing ceiling color", sys);
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[2] = ft_atoi(line);
		}
		else if (ft_ismap(line))
			ft_exception("Wrong first map line", sys);
		else if (ft_strlen(line) > 0)
			ft_exception("Fake line detected", sys);
		free(p_line);
	}
	free(line);
}

int ft_mapmaxwidth(t_list *list_map)
{
	size_t max;

	max = 0;
	while (list_map)
	{
		if (ft_strlen(list_map->content) > max)
			max = ft_strlen(list_map->content);
		list_map = list_map->next;
	}
	return ((int)max);
}

void ft_parseFileCub(int fd, t_system *sys)
{
	t_list *list_map;
	t_list *list_map_temp;
	int i;

	list_map = NULL;
	ft_parseFileCub_bis(fd, sys, &list_map);
	sys->cub.map_H = ft_lstsize(list_map);
	if ((sys->cub.map = (char **)malloc((sys->cub.map_H + 1) * sizeof(char *))) == NULL)
		ft_exception("Malloc fail during map creation (step 1)", sys);
	sys->cub.map_W = ft_mapmaxwidth(list_map);
	i = 0;
	list_map_temp = list_map;
	while (list_map)
	{
		if ((sys->cub.map[i] = ft_strndupfill(list_map->content, sys->cub.map_W, ' ')) == NULL)
			ft_exception("Malloc fail during map creation (step 2)", sys);
		list_map = list_map->next;
		i++;
	}
	sys->cub.map[i] = NULL;
	ft_lstclear(&list_map_temp, free);
	ft_controlError(sys);
}

void ft_print_pixel_exa(int x, int y, int color, t_system *sys)
{
	char *dst;

	dst = sys->frame.addr + (y * sys->frame.line_len + x * (sys->frame.bpp / 8));
	*(unsigned int *)dst = color;
}

void ft_print_pixel(int x, int y, int r, int g, int b, int a, t_system *sys)
{
	int offset = (y * sys->frame.line_len + x * (sys->frame.bpp / 8));

	if (sys->frame.endian == 1) //ARGB
	{
		sys->frame.addr[offset + 0] = a;
		sys->frame.addr[offset + 1] = r;
		sys->frame.addr[offset + 2] = g;
		sys->frame.addr[offset + 3] = b;
	}
	else if (sys->frame.endian == 0) //BGRA
	{
		sys->frame.addr[offset + 0] = b;
		sys->frame.addr[offset + 1] = g;
		sys->frame.addr[offset + 2] = r;
		sys->frame.addr[offset + 3] = a;
	}
}

int ft_key_press(int keycode, t_system *sys)
{
	//ft_printf("keycode: %d\n", keycode);
	if (keycode == 65307 || keycode == 53)
	{
		if (sys->mlx_vars.win)
		{
			mlx_destroy_window(sys->mlx_vars.mlx, sys->mlx_vars.win);
			sys->mlx_vars.win = NULL;
		}
		ft_key_exit(sys);
	}
	//A 97
	else if (keycode == 97 || keycode == 0)
	{
		sys->player.move_x = LEFT;
	}
	//D 100
	else if (keycode == 100 || keycode == 2)
	{
		sys->player.move_x = RIGHT;
	}
	//W 119
	else if (keycode == 119 || keycode == 13)
	{
		sys->player.move_y = UP;
	}
	//S 115
	else if (keycode == 115 || keycode == 1)
	{
		sys->player.move_y = DOWN;
	}
	//<-- 65361
	else if (keycode == 65361 || keycode == 123)
	{
		sys->player.move_r = R_LEFT;
	}
	//--> 65363
	else if (keycode == 65363 || keycode == 124)
	{
		sys->player.move_r = R_RIGHT;
	}
	return (0);
}

int ft_key_release(int keycode, t_system *sys)
{
	//ft_printf("keycode: %d\n", keycode);
	//A 97
	if ((keycode == 97 || keycode == 0) && sys->player.move_x == LEFT)
	{
		sys->player.move_x = 0;
	}
	//D 100
	else if ((keycode == 100 || keycode == 2) && sys->player.move_x == RIGHT)
	{
		sys->player.move_x = 0;
	}
	//W 119
	else if ((keycode == 119 || keycode == 13) && sys->player.move_y == UP)
	{
		sys->player.move_y = 0;
	}
	//S 115
	else if ((keycode == 115 || keycode == 1) && sys->player.move_y == DOWN)
	{
		sys->player.move_y = 0;
	}
	//<-- 65361
	else if ((keycode == 65361 || keycode == 123) && sys->player.move_r == R_LEFT)
	{
		sys->player.move_r = 0;
	}
	//--> 65363
	else if ((keycode == 65363 || keycode == 124) && sys->player.move_r == R_RIGHT)
	{
		sys->player.move_r = 0;
	}
	return (0);
}

int ft_key_exit(t_system *sys)
{
	int i;
	if (sys->cub.txt_N.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_N.img);
	if (sys->cub.txt_S.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_S.img);
	if (sys->cub.txt_W.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_W.img);
	if (sys->cub.txt_E.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_E.img);
	if (sys->cub.txt_SPR.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->cub.txt_SPR.img);
	if (sys->cub.map)
	{
		i = 0;
		while (sys->cub.map[i])
			free(sys->cub.map[i++]);
		free(sys->cub.map);
	}
	if (sys->cub.sprites)
	{
		ft_lstclear(&sys->cub.sprites, free);
		free(sys->cub.sprites);
	}
	if (sys->frame.img)
		mlx_destroy_image(sys->mlx_vars.mlx, sys->frame.img);
	if (sys->mlx_vars.win)
		free(sys->mlx_vars.win);
	if (sys->mlx_vars.mlx)
		mlx_destroy_display(sys->mlx_vars.mlx);
	free(sys->mlx_vars.mlx);
	ft_printf("\n* * * * * * * * * * * * * *\n          by D2435\n* * * * * * * * * * * * * *\n Good bye my little friend\n* * * * * * * * * * * * * *\n");
	exit(0);
}

int ft_next_frame(t_system *sys)
{
	int x;
	double cameraX;
	double rayX;
	double rayY;
	int mapX;
	int mapY;
	double deltaX;
	double deltaY;
	int stepX;
	int stepY;
	int side;
	double sideX;
	double sideY;
	int hit;

	/*GESTIRE SPRITE*/
	x = 0;
	while (x < sys->cub.res_x)
	{
		cameraX = 2 * x / (double)sys->cub.res_x - 1;
		rayX = sys->player.dir_x + sys->player.plane_x * cameraX;
		rayY = sys->player.dir_y + sys->player.plane_y * cameraX;
		/*BUG CASELLA 0*/
		if (sys->player.pos_x < 0)
			mapX = (-1) + (int)sys->player.pos_x;
		else
			mapX = (int)sys->player.pos_x;

		if (sys->player.pos_y < 0)
			mapY = (-1) + (int)sys->player.pos_y;
		else
			mapY = (int)sys->player.pos_y;

		deltaX = fabs(1 / rayX);
		deltaY = fabs(1 / rayY);

		if (rayX < 0)
		{
			stepX = -1;
			sideX = (sys->player.pos_x - mapX) * deltaX;
		}
		else
		{
			stepX = 1;
			sideX = (mapX + 1.0 - sys->player.pos_x) * deltaX;
		}

		if (rayY < 0)
		{
			stepY = -1;
			sideY = (sys->player.pos_y - mapY) * deltaY;
		}
		else
		{
			stepY = 1;
			sideY = (mapY + 1.0 - sys->player.pos_y) * deltaY;
		}

		hit = 0;
		while (!hit)
		{
			if (sideX < sideY)
			{
				sideX += deltaX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideY += deltaY;
				mapY += stepY;
				side = 1;
			}

			/*COLPISCE IL VUOTO*/
			if (((mapX < 0 && stepX < 0) || (mapY < 0 && stepY < 0) || ((mapX >= sys->cub.map_W) && stepX >= 0) || ((mapY >= sys->cub.map_H) && stepY >= 0)))
				hit = 1;
			/*COLPISCE MURI*/
			else if (mapX >= 0 && mapY >= 0 && mapX < sys->cub.map_W && mapY < sys->cub.map_H)
			{
				if (sys->cub.map[mapY][mapX] == '1')
					hit = 1;
			}
		}

		double wallDist;
		double wallX;

		if (side == 0)
			wallDist = (mapX - sys->player.pos_x + (1 - stepX) / 2) / rayX;
		else if (side == 1)
			wallDist = (mapY - sys->player.pos_y + (1 - stepY) / 2) / rayY;

		int lineheight = (int)(sys->cub.res_y / wallDist);
		int drawstart = (int)(-lineheight / 2 + sys->cub.res_y / 2);
		drawstart = drawstart < 0 ? 0 : drawstart;
		drawstart = drawstart > sys->cub.res_y ? sys->cub.res_y : drawstart;
		int drawend = (lineheight / 2 + sys->cub.res_y / 2);
		drawend = drawend > sys->cub.res_y ? sys->cub.res_y : drawend;
		drawend = drawend < 0 ? 0 : drawend;

		if (side == 0)
			wallX = sys->player.pos_y + wallDist * rayY;
		else
			wallX = sys->player.pos_x + wallDist * rayX;
		wallX -= (int)wallX;

		//DISEGNA SOFFITTO
		int y = 0;
		while (y < sys->cub.res_y / 2)
		{
			ft_print_pixel(x, y, sys->cub.c_rgb[0], sys->cub.c_rgb[1], sys->cub.c_rgb[2], 0, sys);
			y++;
		}
		//DISEGNA PAVIMENTO
		while (y < sys->cub.res_y)
		{
			ft_print_pixel(x, y, sys->cub.f_rgb[0], sys->cub.f_rgb[1], sys->cub.f_rgb[2], 0, sys);
			y++;
		}

		/*DISEGNA MURO*/
		t_img_data texture;
		if (side == 0 && rayX < 0)
			texture = sys->cub.txt_E;
		else if (side == 0)
			texture = sys->cub.txt_W;
		else if (side == 1 && rayY < 0)
			texture = sys->cub.txt_S;
		else
			texture = sys->cub.txt_N;

		double wallStep = 1.0 * texture.width / lineheight;
		double texpos = (drawstart - sys->cub.res_y / 2 + lineheight / 2) * wallStep;
		double tex_x = (int)(wallX * (double)texture.width);
		tex_x = texture.width - tex_x - 1;

		while (drawstart <= drawend)
		{
			int _x = (int)fabs(tex_x);
			int _y = (int)fabs(texpos);
			int color = (*(int *)(texture.addr + (_y + (_x * texture.width)) * (texture.bpp / 8)));
			texpos += wallStep;
			ft_print_pixel_exa(x, drawstart++, color, sys);
		}

		/*DISEGNA SPRITES*/
		double sprX;
		double sprY;
		double transX;
		double transY;
		int screenX;
		t_list *sprite = sys->cub.sprites;
		int s_height;
		int s_width;
		int s_startX;
		int s_endX;
		int s_startY;
		int s_endY;
		while (sprite)
		{
			// OK
			sprX = ((t_xy *)(sprite->content))->x - sys->player.pos_x;
			sprY = ((t_xy *)(sprite->content))->y - sys->player.pos_y;

			transX = -0.83 * (sys->player.dir_y * sprX - sys->player.dir_x * sprY);
			transY = -0.83 * (-sys->player.plane_y * sprX + sys->player.plane_x * sprY);

			screenX = (int)((sys->cub.res_x / 2) * (1 + transX / transY));
			s_width = abs((int)(sys->cub.res_y / transY));
			s_height = s_width;

			s_startX = -s_width / 2 + screenX;
			s_endX = s_width / 2 + screenX;
			s_startY = -s_height / 2 + sys->cub.res_y / 2;
			s_endY = s_height / 2 + sys->cub.res_y / 2;

			if (s_startX < 0)
				s_startX = 0;
			if (s_endX > sys->cub.res_x)
				s_endX = sys->cub.res_x;
			if (s_startY < 0)
				s_startY = 0;
			if (s_endY > sys->cub.res_y)
				s_endY = sys->cub.res_y;

			if (x >= s_startX && x < s_endX && transY > 0.1 && transY < wallDist)
			{
				int textX = (int)(256 * (x - (-s_width / 2 + screenX)) * sys->cub.txt_SPR.width / s_width) / 256;
				int textY;
				while (s_startY < s_endY)
				{

					int d = s_startY * 256 - sys->cub.res_y * 128 + s_height * 128;
					textY = ((d * sys->cub.txt_SPR.height) / s_height) / 256;
					int col = (*(int *)(sys->cub.txt_SPR.addr + ((textY + (textX * sys->cub.txt_SPR.width)) * (sys->cub.txt_SPR.bpp / 8))));
					// GREEN MERDA
					if (!(col == (int)0xFF00FF00))
						ft_print_pixel_exa(x, s_startY, col, sys);
					s_startY++;
				}
			}
			sprite = sprite->next;
		}
		x++;
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

		if (sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '0' || sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '2')
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

		if (sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '0' || sys->cub.map[(int)new_pos_y][(int)new_pos_x] == '2')
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
		if (sys->cub.map[(int)new_y][(int)new_x] == '0' || sys->cub.map[(int)new_y][(int)new_x] == '2')
		{
			sys->player.pos_x = new_x;
			sys->player.pos_y = new_y;
		}
	}
	else if (sys->player.move_y == DOWN)
	{
		double new_x = sys->player.pos_x - sys->player.dir_x * sys->player.speed;
		double new_y = sys->player.pos_y - sys->player.dir_y * sys->player.speed;
		if (sys->cub.map[(int)new_y][(int)new_x] == '0' || sys->cub.map[(int)new_y][(int)new_x] == '2')
		{
			sys->player.pos_x = new_x;
			sys->player.pos_y = new_y;
		}
	}
	if (sys->save == 0)
		mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->frame.img, 0, 0);
	return (0);
}

void ft_start_game(t_system *sys)
{
	sys->mlx_vars.win = mlx_new_window(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y, "Cub3D D2435");
	sys->frame.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);
	sys->frame.addr = mlx_get_data_addr(sys->frame.img, &sys->frame.bpp, &sys->frame.line_len, &sys->frame.endian);

	mlx_do_key_autorepeaton(sys->mlx_vars.mlx);
	/* 2 BOTTONE PREMUTO + 0x1 mask BOTTONE PREMUTO*/
	mlx_hook(sys->mlx_vars.win, 2, 0x1, ft_key_press, sys);
	/* 3 BOTTONE RILASCIATO + 0x2 mask BOTTONE RILASCIATO*/
	mlx_hook(sys->mlx_vars.win, 3, 0x2, ft_key_release, sys);
	/* 33 CLIENT MESSAGE + (1L << 17) StructureNotifyMask*/
	mlx_hook(sys->mlx_vars.win, 33, (1L << 17), ft_key_exit, sys);
	/*START DRAWING*/
	mlx_loop_hook(sys->mlx_vars.mlx, ft_next_frame, sys);
	mlx_loop(sys->mlx_vars.mlx);
}

int ft_init_system(t_system *sys)
{
	sys->save = 0;
	sys->frame.img = NULL;
	sys->mlx_vars.mlx = NULL;
	sys->mlx_vars.win = NULL;
	sys->cub.res_x = -1;
	sys->cub.res_y = -1;
	sys->cub.f_rgb[0] = -1;
	sys->cub.f_rgb[1] = -1;
	sys->cub.f_rgb[2] = -1;
	sys->cub.c_rgb[0] = -1;
	sys->cub.c_rgb[1] = -1;
	sys->cub.c_rgb[2] = -1;
	sys->cub.map = NULL;
	sys->cub.map_W = -1;
	sys->cub.map_H = -1;
	sys->cub.txt_N.img = NULL;
	sys->cub.txt_S.img = NULL;
	sys->cub.txt_W.img = NULL;
	sys->cub.txt_E.img = NULL;
	sys->cub.txt_SPR.img = NULL;
	sys->cub.n_sprites = 0;
	sys->cub.sprites = NULL;
	sys->player.pos_x = -1;
	sys->player.pos_y = -1;
	sys->player.dir_x = 0;
	sys->player.dir_y = 0;
	sys->player.plane_x = 0;
	sys->player.plane_y = 0;
	sys->player.speed = 0;
	sys->player.move_x = 0;
	sys->player.move_y = 0;
	sys->player.move_r = 0;
	return (0);
}

int ft_is_cub_file(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len <= 4)
		return (0);
	return (!ft_strcmp(str + (len - 4), ".cub"));
}

void ft_write_on_file(t_system *sys, int fd, const void *buf, ssize_t len)
{
	if (write(fd, buf, len) != len)
	{
		ft_exception("Fail write on bmp file", sys);
	}
}

int ft_save_frame(t_system *sys)
{
	int fd;
	int i;
	unsigned int *line;
	t_bmp bmp;

	sys->frame.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);
	sys->frame.addr = mlx_get_data_addr(sys->frame.img, &sys->frame.bpp, &sys->frame.line_len, &sys->frame.endian);

	bmp.tot_size = (sys->cub.res_x * sys->cub.res_y * (sys->frame.bpp / 8)) + 54;
	bmp.pixel_offset = 54;
	bmp.h_size = 40;
	bmp.w = sys->cub.res_x;
	bmp.h = sys->cub.res_y;
	bmp.planes = 1;
	bmp.bpp = sys->frame.bpp;
	bmp.img_size = sys->cub.res_x * sys->cub.res_y * (sys->frame.bpp / 8);
	sys->save = 1;

	ft_next_frame(sys);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		ft_exception("Can't open/create screenshot file", sys);
	ft_write_on_file(sys, fd, "BM", 2);
	ft_write_on_file(sys, fd, &bmp, sizeof(bmp));
	i = 0;
	while (i < sys->cub.res_y)
	{
		line = (unsigned int *)&sys->frame.addr[(sys->cub.res_y - i - 1) * sys->frame.line_len];
		ft_write_on_file(sys, fd, line, sys->frame.line_len);
		i++;
	}
	if (close(fd) == -1)
		ft_exception("Can't close bmp file", sys);
	return (0);
}

int main(int argc, char **argv)
{
	t_system sys;

	if (argc == 1)
		ft_exception("No map send", &sys);
	else if (argc > 3)
		ft_exception("Too many arguments", &sys);

	ft_init_system(&sys);
	sys.mlx_vars.mlx = mlx_init();
	if (!sys.mlx_vars.mlx)
		ft_exception("Mlx failed start", &sys);

	/* PARSING map */
	if (!ft_is_cub_file(argv[1]))
		ft_exception("Not .cub file selected", &sys);
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exception("Insert a valid .cub file", &sys);
	ft_parseFileCub(fd, &sys);
	if (close(fd) == -1)
		ft_exception("Can't close cub file", &sys);
	/*SCREENSHOT*/
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
			ft_save_frame(&sys);
		else
			ft_exception("Command not found", &sys);
		ft_key_exit(&sys);
	}
	/*START GAME*/
	ft_start_game(&sys);
	return (0);
}