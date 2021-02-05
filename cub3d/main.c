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

#define R_LEFT 10
#define R_RIGTH 20
#define LEFT 30
#define RIGHT 40
#define UP 50
#define DOWN 60

typedef struct s_img_data
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
	int width;
	int heigth;
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
	int move;
} t_player;

typedef struct s_system
{
	t_cub cub;
	t_img_data frame;
	t_mlx_vars mlx_vars;
	t_player player;

} t_system;

void ft_print_pixel(int x, int y, int r, int g, int b, int a, t_system *sys);

void ft_exception(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(-1);
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
		sys->player.plane_x = (((double)sys->cub.map_W / (double)sys->cub.map_H) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'S')
	{
		sys->player.dir_y = 1;
		sys->player.plane_x = -(((double)sys->cub.map_W / (double)sys->cub.map_H) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'E')
	{
		sys->player.dir_x = 1;
		sys->player.plane_y = (((double)sys->cub.map_W / (double)sys->cub.map_H) - 1.0);
	}
	else if (sys->cub.map[y][x] == 'W')
	{
		sys->player.dir_x = -1;
		sys->player.plane_y = -(((double)sys->cub.map_W / (double)sys->cub.map_H) - 1.0);
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

int ft_controlMapBorder(t_system *sys)
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
		ft_exception("Resolution X not valid");
	if (sys->cub.res_y <= 0)
		ft_exception("Resolution Y not valid");
	if (sys->cub.txt_N.img == NULL)
		ft_exception("North texture NULL");
	sys->cub.txt_N.addr = mlx_get_data_addr(sys->cub.txt_N.img, &sys->cub.txt_N.bpp, &sys->cub.txt_N.line_len, &sys->cub.txt_N.endian);
	if (sys->cub.txt_S.img == NULL)
		ft_exception("South texture NULL");
	sys->cub.txt_S.addr = mlx_get_data_addr(sys->cub.txt_S.img, &sys->cub.txt_S.bpp, &sys->cub.txt_S.line_len, &sys->cub.txt_S.endian);
	if (sys->cub.txt_W.img == NULL)
		ft_exception("West texture NULL");
	sys->cub.txt_W.addr = mlx_get_data_addr(sys->cub.txt_W.img, &sys->cub.txt_W.bpp, &sys->cub.txt_W.line_len, &sys->cub.txt_W.endian);
	if (sys->cub.txt_E.img == NULL)
		ft_exception("East texture NULL");
	sys->cub.txt_E.addr = mlx_get_data_addr(sys->cub.txt_E.img, &sys->cub.txt_E.bpp, &sys->cub.txt_E.line_len, &sys->cub.txt_E.endian);
	if (sys->cub.txt_SPR.img == NULL)
		ft_exception("Sprite texture NULL");
	sys->cub.txt_SPR.addr = mlx_get_data_addr(sys->cub.txt_SPR.img, &sys->cub.txt_SPR.bpp, &sys->cub.txt_SPR.line_len, &sys->cub.txt_SPR.endian);
	if (sys->cub.f_rgb[0] < 0 || sys->cub.f_rgb[0] > 255 ||
		sys->cub.f_rgb[1] < 0 || sys->cub.f_rgb[1] > 255 ||
		sys->cub.f_rgb[2] < 0 || sys->cub.f_rgb[2] > 255)
		ft_exception("Floor color values");
	if (sys->cub.c_rgb[0] < 0 || sys->cub.c_rgb[0] > 255 ||
		sys->cub.c_rgb[1] < 0 || sys->cub.c_rgb[1] > 255 ||
		sys->cub.c_rgb[2] < 0 || sys->cub.c_rgb[2] > 255)
		ft_exception("Ceiling color values");
	if (sys->cub.map_W < 3)
		ft_exception("Map width too small");
	if (sys->cub.map_H < 3)
		ft_exception("Map height too small");
	ret = ft_controlMapBorder(sys);
	if (ret == 0)
		ft_exception("Map border open");
	else if (ret == -2)
		ft_exception("Multyplayer not allowed");
	else if (ret == -1)
		ft_exception("No player spawn point");
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
				ft_exception("Duplicated map");
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
		if (line[0] == 'R' && ft_isspace(line[1]))
		{
			if (sys->cub.res_x != -1 && sys->cub.res_y != -1)
				ft_exception("Duplicated resolution");
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
				ft_exception("Duplicated north texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_N.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_N.width, &sys->cub.txt_N.heigth);
		}
		else if (*line == 'S' && *(line + 1) == 'O' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_S.img != NULL)
				ft_exception("Duplicated south texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_S.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_S.width, &sys->cub.txt_S.heigth);
		}
		else if (*line == 'W' && *(line + 1) == 'E' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_W.img != NULL)
				ft_exception("Duplicated west texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_W.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_W.width, &sys->cub.txt_W.heigth);
		}
		else if (*line == 'E' && *(line + 1) == 'A' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_E.img != NULL)
				ft_exception("Duplicated east texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_E.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_E.width, &sys->cub.txt_E.heigth);
		}
		else if (*line == 'S' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.txt_SPR.img != NULL)
				ft_exception("Duplicated sprite texture");
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_SPR.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_SPR.width, &sys->cub.txt_SPR.heigth);
		}
		else if (*line == 'F' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.f_rgb[0] != -1 && sys->cub.f_rgb[1] != -1 && sys->cub.f_rgb[2] != -1)
				ft_exception("Duplicated floor color");
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing floor color");
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
				ft_exception("Parsing floor color");
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[2] = ft_atoi(line);
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			if (sys->cub.c_rgb[0] != -1 && sys->cub.c_rgb[1] != -1 && sys->cub.c_rgb[2] != -1)
				ft_exception("Duplicated ceiling color");
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
				ft_exception("Parsing ceiling color");
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
				ft_exception("Parsing ceiling color");
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[2] = ft_atoi(line);
		}
		else if (ft_ismap(line))
			ft_exception("Wrong first map line");
		else if (ft_strlen(line) > 0)
			ft_exception("Fake line detected");
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
		ft_exception("Malloc fail during map creation (step 1)");
	sys->cub.map_W = ft_mapmaxwidth(list_map);
	i = 0;
	list_map_temp = list_map;
	while (list_map)
	{
		if ((sys->cub.map[i] = ft_strndupfill(list_map->content, sys->cub.map_W, ' ')) == NULL)
			ft_exception("Malloc fail during map creation (step 2)");
		list_map = list_map->next;
		i++;
	}
	sys->cub.map[i] = NULL;
	ft_lstclear(&list_map_temp, free);
	ft_controlError(sys);
}

void ft_printCub(t_cub cub)
{
	ft_printf("res_x: %d  res_y: %d\n", cub.res_x, cub.res_y);
	ft_printf("txt_N: %s\n", cub.txt_N);
	ft_printf("txt_S: %s\n", cub.txt_S);
	ft_printf("txt_W: %s\n", cub.txt_W);
	ft_printf("txt_E: %s\n", cub.txt_E);
	ft_printf("txt_SPR: %s\n", cub.txt_SPR);
	ft_printf("f_rgb [R: %d, G: %d, B: %d]\n", cub.f_rgb[0], cub.f_rgb[1], cub.f_rgb[2]);
	ft_printf("c_rgb [R: %d, G: %d, B: %d]\n", cub.c_rgb[0], cub.c_rgb[1], cub.c_rgb[2]);
	ft_printf("MAP_SIZE [WIDTH: %d, HEIGHT: %d]\n", cub.map_W, cub.map_H);
	ft_printf("map:\n");
	while (*cub.map)
		ft_printf("--> %s\n", *cub.map++);
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

void ft_keys(int keycode, t_system *sys)
{
	double moveSpeed = 0.2;
	//ft_printf("keycode: %d\n", keycode);
	//ESC 65307
	if (keycode == 65307 || keycode == 53)
	{
		ft_printf("Good bye my little friend..\n");
		exit(0);
	}
	//A 97
	else if (keycode == 97 || keycode == 0)
	{
		ft_printf("LEFT\n");
	}
	//D 100
	else if (keycode == 100 || keycode == 2)
	{
		ft_printf("RIGHT\n");
	}
	//W 119
	else if (keycode == 119 || keycode == 13)
	{
		ft_printf("UP\n");
	}
	//S 115
	else if (keycode == 115 || keycode == 1)
	{
		ft_printf("DOWN\n");
	}
	//<-- 65361
	else if (keycode == 65361 || keycode == 123)
	{
		ft_printf("TURN LEFT\n");
		sys->player.move = R_LEFT;
	}
	//--> 65363
	else if (keycode == 65363 || keycode == 124)
	{
		ft_printf("TURN RIGHT\n");
	}
}

void ft_print_player(t_system *sys)
{
	printf("posX: %.2lf", sys->player.pos_x);
	printf(" posY: %.2lf", sys->player.pos_y);
	printf(" dirX: %.2lf", sys->player.dir_x);
	printf(" dirY: %.2lf", sys->player.dir_y);
	printf(" planeX: %.2lf", sys->player.plane_x);
	printf(" planeY: %.2lf\n", sys->player.plane_y);
	// NORD		posX: 25.50 posY: 3.50 dirX:  0.00 dirY: -1.00 planeX:  1.06 planeY:  0.00
	// SUD		posX: 25.50 posY: 3.50 dirX:  0.00 dirY:  1.00 planeX: -1.06 planeY:  0.00
	// OVEST	posX: 25.50 posY: 3.50 dirX: -1.00 dirY:  0.00 planeX:  0.00 planeY: -1.06
	// EST		posX: 25.50 posY: 3.50 dirX:  1.00 dirY:  0.00 planeX:  0.00 planeY:  1.06
}

void ft_next_frame(t_system *sys)
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
		drawstart = (drawstart > sys->cub.res_y) ? sys->cub.res_y : drawstart;
		int drawend = (lineheight / 2 + sys->cub.res_y / 2);
		drawend = (drawend > sys->cub.res_y) ? sys->cub.res_y : drawend;
		drawend = (drawend < 0) ? 0 : drawend;

		if (side == 0)
			wallX = sys->player.pos_y + wallDist * rayY;
		else if (side <= 2)
			wallX = sys->player.pos_x + wallDist * rayX;
		wallX -= (int)wallX;

		/*DISEGNA SPRITES*/

		/*DISEGNA SOFFITTO*/
		int y = 0;
		while (y < sys->cub.res_y / 2)
		{
			ft_print_pixel(x, y, sys->cub.c_rgb[0], sys->cub.c_rgb[1], sys->cub.c_rgb[2], 0, sys);
			y++;
		}
		/*DISEGNA PAVIMENTO*/
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
		if (side == 1 && rayY < 0)
			texture = sys->cub.txt_S;
		else
			texture = sys->cub.txt_N;

		double wallStep = 1.0 * texture.width / lineheight;
		double texpos = (drawstart - sys->cub.res_y / 2 + lineheight / 2) * wallStep;
		double tex_x = (int)(wallX * (double)texture.width);
		tex_x = texture.width - tex_x - 1;
		double tex_y = 0;

		while (drawstart <= drawend)
		{
			tex_y = (int)texpos;
			int color = (*(int *)(texture.addr + ((abs(tex_x) + (abs(tex_y) * texture.width)) * (texture.bpp / 8))));
			texpos += wallStep;
			ft_print_pixel_exa(x, drawstart++, color, sys);
		}

		x++;
	}
	/*MOVIMENTO PLAYER*/
	if (sys->player.move != R_LEFT)
	{
		double olddirx;
		double oldplanex;

		olddirx = sys->player.dir_x;
		sys->player.dir_x = (sys->player.dir_x * cos(-0.02)) - (sys->player.dir_y * sin(-0.02));
		sys->player.dir_x = (olddirx * sin(-0.02)) + (sys->player.dir_y * cos(-0.02));

		oldplanex = sys->player.plane_x;
		sys->player.plane_x = (sys->player.plane_x * cos(-0.02)) - (sys->player.plane_y * sin(-0.02));
		sys->player.plane_y = (oldplanex * sin(-0.02)) + (sys->player.plane_y * cos(-0.02));
		sys->player.move == 0;
	}
	if (sys->player.move == R_RIGTH)
	{
	}
	if (sys->player.move == LEFT)
	{
	}
	if (sys->player.move == RIGHT)
	{
	}
	if (sys->player.move == UP)
	{
	}
	if (sys->player.move == DOWN)
	{
	}

	mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->frame.img, 0, 0);
}

void ft_start_game(t_system *sys)
{
	sys->mlx_vars.win = mlx_new_window(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y, "Cub3D D2435");
	sys->frame.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);
	sys->frame.addr = mlx_get_data_addr(sys->frame.img, &sys->frame.bpp, &sys->frame.line_len, &sys->frame.endian);

	mlx_key_hook(sys->mlx_vars.win, ft_keys, &sys);
	mlx_loop_hook(sys->mlx_vars.mlx, ft_next_frame, sys);
	mlx_loop(sys->mlx_vars.mlx);
}

int ft_init_system(t_system *sys)
{
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
	ft_memset(&sys->cub.txt_N, 0, sizeof(t_img_data));
	ft_memset(&sys->cub.txt_S, 0, sizeof(t_img_data));
	ft_memset(&sys->cub.txt_W, 0, sizeof(t_img_data));
	ft_memset(&sys->cub.txt_E, 0, sizeof(t_img_data));
	ft_memset(&sys->cub.txt_S, 0, sizeof(t_img_data));
	sys->player.pos_x = -1;
	sys->player.pos_y = -1;
	sys->player.dir_x = 0;
	sys->player.dir_y = 0;
	sys->player.plane_x = 0;
	sys->player.plane_y = 0;
	sys->player.speed = 0;
	sys->player.move = 0;
	return (0);
}

int main(int argc, char **argv)
{
	t_system sys;
	void *mlx;
	int win_x;
	int win_y;

	if (argc == 1)
		ft_exception("No map send");
	else if (argc > 3)
		ft_exception("Too many arguments");

	ft_init_system(&sys);
	sys.mlx_vars.mlx = mlx_init();
	if (!sys.mlx_vars.mlx)
		ft_exception("Mlx failed start");

	/* PARSING map */
	int fd = open(argv[1], O_RDONLY);
	ft_parseFileCub(fd, &sys);
	close(fd);
	//ft_printCub(sys.cub);

	//mlx_get_screen_size(mlx, &win_x, &win_y);
	//if (cub.res_x > win_x || cub.res_y > win_y)
	//	ft_exception("Resolution not supported");

	ft_start_game(&sys);
	return (0);
}