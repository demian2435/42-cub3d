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

#include <math.h>
#include <fcntl.h>
#include "mlx.h"
#include "libft.h"


typedef struct s_cub
{
	int res_x;
	int res_y;
	char *txt_N;
	char *txt_S;
	char *txt_W;
	char *txt_E;
	char *txt_SPR;
	int f_rgb[3];
	int c_rgb[3];
	char **map;
	int map_W;
	int map_H;
} t_cub;

typedef struct s_img_data
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
} t_img_data;

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
	char move;
} t_player;

typedef struct s_system
{
	t_cub cub;
	t_img_data img;
	t_mlx_vars mlx_vars;
	t_player player;

} t_system;

void ft_print_pixel(int x, int y, int r, int g, int b, int a, t_system *sys);

void ft_freecub(t_cub *cub)
{
	int i;

	free(cub->txt_N);
	free(cub->txt_S);
	free(cub->txt_W);
	free(cub->txt_E);
	free(cub->txt_SPR);
	i = 0;
	while (cub->map[i])
		free(cub->map[i++]);
	free(cub->map);
}

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
				if (sys->cub.map[y][x] == 'N')
				{
					count++;
					sys->player.pos_x = x;
					sys->player.pos_y = y;
					sys->player.dir_x = 0;
					sys->player.dir_y = 1;
				}
				else if (sys->cub.map[y][x] == 'S')
				{
					count++;
					sys->player.pos_x = x;
					sys->player.pos_y = y;
					sys->player.dir_x = 0;
					sys->player.dir_y = -1;
				}
				else if (sys->cub.map[y][x] == 'W')
				{
					count++;
					sys->player.pos_x = x;
					sys->player.pos_y = y;
					sys->player.dir_x = -1;
					sys->player.dir_y = 0;
				}
				else if (sys->cub.map[y][x] == 'E')
				{
					count++;
					sys->player.pos_x = x;
					sys->player.pos_y = y;
					sys->player.dir_x = 1;
					sys->player.dir_y = 0;
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
	if (sys->cub.txt_N == NULL)
		ft_exception("North texture NULL");
	if (sys->cub.txt_S == NULL)
		ft_exception("South texture NULL");
	if (sys->cub.txt_W == NULL)
		ft_exception("West texture NULL");
	if (sys->cub.txt_E == NULL)
		ft_exception("East texture NULL");
	if (sys->cub.txt_SPR == NULL)
		ft_exception("Sprite texture NULL");
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

static void ft_parseFileCub_bis(int fd, t_cub *cub, t_list **list_map)
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
			if (cub->res_x != -1 && cub->res_y != -1)
				ft_exception("Duplicated resolution");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->res_x = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			cub->res_y = ft_atoi(line);
		}
		else if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		{
			if (cub->txt_N != NULL)
				ft_exception("Duplicated north texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->txt_N = ft_strdup(line);
		}
		else if (*line == 'S' && *(line + 1) == 'O' && ft_isspace(*(line + 2)))
		{
			if (cub->txt_S != NULL)
				ft_exception("Duplicated south texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->txt_S = ft_strdup(line);
		}
		else if (*line == 'W' && *(line + 1) == 'E' && ft_isspace(*(line + 2)))
		{
			if (cub->txt_W != NULL)
				ft_exception("Duplicated west texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->txt_W = ft_strdup(line);
		}
		else if (*line == 'E' && *(line + 1) == 'A' && ft_isspace(*(line + 2)))
		{
			if (cub->txt_E != NULL)
				ft_exception("Duplicated east texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->txt_E = ft_strdup(line);
		}
		else if (*line == 'S' && ft_isspace(*(line + 1)))
		{
			if (cub->txt_SPR != NULL)
				ft_exception("Duplicated sprite texture");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->txt_SPR = ft_strdup(line);
		}
		else if (*line == 'F' && ft_isspace(*(line + 1)))
		{
			if (cub->f_rgb[0] != -1 && cub->f_rgb[1] != -1 && cub->f_rgb[2] != -1)
				ft_exception("Duplicated floor color");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->f_rgb[0] = ft_atoi(line);
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
			cub->f_rgb[1] = ft_atoi(line);
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
			cub->f_rgb[2] = ft_atoi(line);
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			if (cub->c_rgb[0] != -1 && cub->c_rgb[1] != -1 && cub->c_rgb[2] != -1)
				ft_exception("Duplicated ceiling color");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->c_rgb[0] = ft_atoi(line);
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
			cub->c_rgb[1] = ft_atoi(line);
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
			cub->c_rgb[2] = ft_atoi(line);
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
	ft_parseFileCub_bis(fd, &sys->cub, &list_map);
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


/*      //draw the pixels of the stripe as a vertical line
      ft_print_verLine(x, drawStart, drawEnd, color);*/

int ft_print_verLine (int x, int start, int stop, int color, t_system *sys)
{
	for (int _y = 0; _y < sys->cub.res_y; ++_y)
	{
		if(_y >= start && _y <= stop)
			ft_print_pixel(x, _y, 255, 0, 0, 0, sys);
	}
	return (0);
}

int test(t_system *sys)
{
	mlx_destroy_image(sys->mlx_vars.mlx, sys->img.img);

	sys->img.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);

	sys->img.addr = mlx_get_data_addr(sys->img.img, &sys->img.bpp, &sys->img.line_len, &sys->img.endian);

		/*print sky*/
	for (int y = 0; y < sys->cub.res_y / 2; ++y)
	{
		for (int x = 0; x < sys->cub.res_x; ++x)
		{
			ft_print_pixel(x, y, sys->cub.c_rgb[0], sys->cub.c_rgb[1], sys->cub.c_rgb[2], 0, sys);
		}
	}
	/*print floor*/
	for (int y = sys->cub.res_y / 2; y < sys->cub.res_y; ++y)
	{
		for (int x = 0; x < sys->cub.res_x; ++x)
		{
			ft_print_pixel(x, y, sys->cub.f_rgb[0], sys->cub.f_rgb[1], sys->cub.f_rgb[2], 0, sys);
		}
	}
	
	double posX = sys->player.pos_x;
	double posY = sys->player.pos_y;  //x and y start position
	double dirX = sys->player.dir_x;
	double dirY = sys->player.dir_y; //initial direction vector
	double planeX = sys->player.plane_x;
	double planeY = sys->player.plane_y; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	for(int x = 0; x < sys->cub.res_x; x++)
	{
		
		//calculate ray position and direction
		double cameraX = 2.0 * x / (double)sys->cub.res_x - 1.0; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			}
			else
			{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			}
			//Check if ray has hit a wall
			if(sys->cub.map[mapY][mapX] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - posX + (1.0 - stepX) / 2.0) / rayDirX;
		else          perpWallDist = (mapY - posY + (1.0 - stepY) / 2.0) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(sys->cub.res_y / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + sys->cub.res_y / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + sys->cub.res_y/ 2;
		if(drawEnd >= sys->cub.res_y)drawEnd = sys->cub.res_y - 1;

		//choose wall color
		/*
		int color;
		switch(sys->cub.map[mapY][mapX])
		{
			case 1:  color = 0XFF000000; break;
			case 2:  color = 0x0000FF00; break;
			default: color = 0X00000000; break;
		}

		//give x and y sides different brightness
		//if(side == 1) {color = color / 2;}

		*/
		//draw the pixels of the stripe as a vertical line
		ft_print_verLine(x, drawStart, drawEnd, 0, sys);
		//ft_print_verLine(x, 0, 0, color, sys);
		
	
		//timing for input and FPS counter
		//oldTime = time;
		//time = ;
		//double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		//ft_printf("FPS: %d\n", 1.0 / frameTime); //FPS counter

		//speed modifiers
		//double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		//double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

		
		//move forward if no wall in front of you
		if(sys->player.move == 'U')
		{
			//if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
			//if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
			sys->player.pos_x += dirX;
			sys->player.pos_y += dirY;
			sys->player.move = '0';
			ft_printf("AVANTI");
		}
		/*
		//move backwards if no wall behind you
		else if(sys->player.move == 'D')
		{
			if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
			if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}
		//rotate to the right
		else if(sys->player.move == '+')
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		//rotate to the left
		else if(sys->player.move == '-')
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}
	*/
	}

	mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->img.img, 0, 0);

  	return (0);
}

void ft_print_pixel(int x, int y, int r, int g, int b, int a, t_system *sys)
{
	int offset = (y * sys->img.line_len + x * (sys->img.bpp / 8));

	if (sys->img.endian == 1) //ARGB
	{
		sys->img.addr[offset + 0] = a;
		sys->img.addr[offset + 1] = r;
		sys->img.addr[offset + 2] = g;
		sys->img.addr[offset + 3] = b;
	}
	else if (sys->img.endian == 0) //BGRA
	{
		sys->img.addr[offset + 0] = b;
		sys->img.addr[offset + 1] = g;
		sys->img.addr[offset + 2] = r;
		sys->img.addr[offset + 3] = a;
	}
}

int key_hook(int keycode, t_system *sys)
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
		sys->player.move = 'L';
	}
	//D 100
	else if (keycode == 100 || keycode == 2)
	{
		ft_printf("RIGHT\n");
		sys->player.move = 'R';
	}
	//W 119
	else if (keycode == 119 || keycode == 13)
	{
		ft_printf("UP\n");
		sys->player.move = 'U';
	}
	//S 115
	else if (keycode == 115 || keycode == 1)
	{
		ft_printf("DOWN\n");
		sys->player.move = 'D';
	}
	//<-- 65361
	else if (keycode == 65361 || keycode == 123)
	{
		ft_printf("TURN LEFT\n");
		sys->player.move = '-';
	}
	//--> 65363
	else if (keycode == 65363 || keycode == 124)
	{
		ft_printf("TURN RIGHT\n");
		sys->player.move = '+';
	}
	return (0);
}

void ft_render_next_frame(t_system *sys)
{
	mlx_destroy_image(sys->mlx_vars.mlx, sys->img.img);

	sys->img.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);

	sys->img.addr = mlx_get_data_addr(sys->img.img, &sys->img.bpp, &sys->img.line_len, &sys->img.endian);
	//sys->cub.c_rgb[0]++;

	/*print sky*/
	for (int y = 0; y < sys->cub.res_y / 2; ++y)
	{
		for (int x = 0; x < sys->cub.res_x; ++x)
		{
			ft_print_pixel(x, y, sys->cub.c_rgb[0], sys->cub.c_rgb[1], sys->cub.c_rgb[2], 0, sys);
		}
	}
	/*print floor*/
	for (int y = sys->cub.res_y / 2; y < sys->cub.res_y; ++y)
	{
		for (int x = 0; x < sys->cub.res_x; ++x)
		{
			ft_print_pixel(x, y, sys->cub.f_rgb[0], sys->cub.f_rgb[1], sys->cub.f_rgb[2], 0, sys);
		}
	}

	/* MOSCA XD*/
	int r_x = rand() % sys->cub.res_x;
	int r_y = rand() % sys->cub.res_y;
	ft_print_pixel(r_x, r_y, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x + 1, r_y + 1, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x - 1, r_y - 1, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x - 1, r_y + 1, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x + 1, r_y - 1, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x + 2, r_y + 2, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x - 2, r_y - 2, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x - 2, r_y + 2, 0, 0, 0, 0, sys);
	ft_print_pixel(r_x + 2, r_y - 2, 0, 0, 0, 0, sys);
	/*FINE MOSCA*/

	mlx_put_image_to_window(sys->mlx_vars.mlx, sys->mlx_vars.win, sys->img.img, 0, 0);
}

void screen(t_system *sys)
{
	/* WINDOW */
	sys->mlx_vars.win = mlx_new_window(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y, "Cub3D D2435");

	sys->img.img = mlx_new_image(sys->mlx_vars.mlx, sys->cub.res_x, sys->cub.res_y);

	sys->img.addr = mlx_get_data_addr(sys->img.img, &sys->img.bpp, &sys->img.line_len, &sys->img.endian);

	mlx_key_hook(sys->mlx_vars.win, key_hook, &sys);

	//mlx_loop_hook(sys->mlx_vars.mlx, ft_render_next_frame, sys);
	mlx_loop_hook(sys->mlx_vars.mlx, test, sys);

	mlx_loop(sys->mlx_vars.mlx);
}

int ft_init_system(t_system *sys)
{
	sys->cub.res_x = -1;
	sys->cub.res_y = -1;
	sys->cub.txt_N = NULL;
	sys->cub.txt_S = NULL;
	sys->cub.txt_W = NULL;
	sys->cub.txt_E = NULL;
	sys->cub.txt_SPR = NULL;
	sys->cub.f_rgb[0] = -1;
	sys->cub.f_rgb[1] = -1;
	sys->cub.f_rgb[2] = -1;
	sys->cub.c_rgb[0] = -1;
	sys->cub.c_rgb[1] = -1;
	sys->cub.c_rgb[2] = -1;
	sys->cub.map = NULL;
	sys->cub.map_W = -1;
	sys->cub.map_H = -1;

	sys->player.pos_x = -1;
	sys->player.pos_y = -1;
	sys->player.dir_x = 0;
	sys->player.dir_y = 0;
	sys->player.plane_x = 0;
	sys->player.plane_y = 0.66;
	sys->player.move = '0';

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

	/* PARSING map */
	int fd = open(argv[1], O_RDONLY);
	ft_init_system(&sys);

	ft_parseFileCub(fd, &sys);
	close(fd);
	//ft_printCub(sys.cub);

	sys.mlx_vars.mlx = mlx_init();
	if (!sys.mlx_vars.mlx)
		ft_exception("Mlx failed start");

	//mlx_get_screen_size(mlx, &win_x, &win_y);
	//if (cub.res_x > win_x || cub.res_y > win_y)
	//	ft_exception("Resolution not supported");

	screen(&sys);
	/*FINE*/
	ft_freecub(&sys.cub);
	return (0);
}