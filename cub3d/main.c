/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 18:38:52 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/03 11:14:21 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_cub
{
	int RESOLUTION_X;
	int RESOLUTION_Y;
	char *TEXTURE_NORTH;
	char *TEXTURE_SOUTH;
	char *TEXTURE_WEST;
	char *TEXTURE_EAST;
	char *TEXTURE_SPRITE;
	int FLOOR_COLOR[3];
	int CEILING_COLOR[3];
	char **MAP;
	int MAP_WIDTH;
	int MAP_HEIGHT;
	int START_DIR;
	int START_X;
	int START_Y;
} t_cub;

void ft_freecub(t_cub *cub)
{
	int i;

	free(cub->TEXTURE_NORTH);
	cub->TEXTURE_NORTH = NULL;
	free(cub->TEXTURE_SOUTH);
	cub->TEXTURE_SOUTH = NULL;
	free(cub->TEXTURE_WEST);
	cub->TEXTURE_WEST = NULL;
	free(cub->TEXTURE_EAST);
	cub->TEXTURE_EAST = NULL;
	free(cub->TEXTURE_SPRITE);
	cub->TEXTURE_SPRITE = NULL;
	i = 0;
	while (cub->MAP[i])
		free(cub->MAP[i++]);
	free(cub->MAP);
}

void ft_exception(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(-1);
}

void ft_initCub(t_cub *cub)
{
	cub->RESOLUTION_X = -1;
	cub->RESOLUTION_Y = -1;
	cub->TEXTURE_NORTH = NULL;
	cub->TEXTURE_SOUTH = NULL;
	cub->TEXTURE_WEST = NULL;
	cub->TEXTURE_EAST = NULL;
	cub->TEXTURE_SPRITE = NULL;
	cub->FLOOR_COLOR[0] = -1;
	cub->FLOOR_COLOR[1] = -1;
	cub->FLOOR_COLOR[2] = -1;
	cub->CEILING_COLOR[0] = -1;
	cub->CEILING_COLOR[1] = -1;
	cub->CEILING_COLOR[2] = -1;
	cub->MAP = NULL;
	cub->MAP_WIDTH = -1;
	cub->MAP_HEIGHT = -1;
	cub->START_DIR = 'X';
	cub->START_X = -1;
	cub->START_Y = -1;
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

int ft_controlMapBorder(t_cub *cub)
{
	int x;
	int y;
	int count;

	count = 0;
	y = 0;
	while (y < cub->MAP_HEIGHT)
	{
		x = 0;
		while (x < cub->MAP_WIDTH)
		{
			if (cub->MAP[y][x] == '0' || cub->MAP[y][x] == '2' || cub->MAP[y][x] == 'N' || cub->MAP[y][x] == 'S' || cub->MAP[y][x] == 'W' || cub->MAP[y][x] == 'E')
			{
				if (x == 0 || y == 0 || y == cub->MAP_HEIGHT - 1 || x == cub->MAP_WIDTH - 1)
					return (0);
				if (ft_isSpaceNear(cub->MAP, x, y))
					return (0);
				if (ft_isalpha(cub->MAP[y][x]))
				{
					count++;
					cub->START_DIR = cub->MAP[y][x];
					cub->START_X = x;
					cub->START_Y = y;
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

void ft_controlErrorCub(t_cub *cub)
{
	int ret;
	
	if (cub->RESOLUTION_X <= 0)
		ft_exception("Resolution X not valid");
	if (cub->RESOLUTION_Y <= 0)
		ft_exception("Resolution Y not valid");
	if (cub->TEXTURE_NORTH == NULL)
		ft_exception("North texture NULL");
	if (cub->TEXTURE_SOUTH == NULL)
		ft_exception("South texture NULL");
	if (cub->TEXTURE_WEST == NULL)
		ft_exception("West texture NULL");
	if (cub->TEXTURE_EAST == NULL)
		ft_exception("East texture NULL");
	if (cub->TEXTURE_SPRITE == NULL)
		ft_exception("Sprite texture NULL");
	if (cub->FLOOR_COLOR[0] < 0 || cub->FLOOR_COLOR[0] > 255 ||
		cub->FLOOR_COLOR[1] < 0 || cub->FLOOR_COLOR[1] > 255 ||
		cub->FLOOR_COLOR[2] < 0 || cub->FLOOR_COLOR[2] > 255)
		ft_exception("Floor color values");
	if (cub->CEILING_COLOR[0] < 0 || cub->CEILING_COLOR[0] > 255 ||
		cub->CEILING_COLOR[1] < 0 || cub->CEILING_COLOR[1] > 255 ||
		cub->CEILING_COLOR[2] < 0 || cub->CEILING_COLOR[2] > 255)
		ft_exception("Ceiling color values");
	if (cub->MAP_WIDTH < 3)
		ft_exception("Map width too small");
	if (cub->MAP_HEIGHT < 3)
		ft_exception("Map height too small");
	ret = ft_controlMapBorder(cub);
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
			if (cub->RESOLUTION_X != -1 && cub->RESOLUTION_Y != -1)
				ft_exception("Duplicated resolution");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->RESOLUTION_X = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			cub->RESOLUTION_Y = ft_atoi(line);
		}
		else if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		{
			if (cub->TEXTURE_NORTH != NULL)
				ft_exception("Duplicated north texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->TEXTURE_NORTH = ft_strdup(line);
		}
		else if (*line == 'S' && *(line + 1) == 'O' && ft_isspace(*(line + 2)))
		{
			if (cub->TEXTURE_SOUTH != NULL)
				ft_exception("Duplicated south texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->TEXTURE_SOUTH = ft_strdup(line);
		}
		else if (*line == 'W' && *(line + 1) == 'E' && ft_isspace(*(line + 2)))
		{
			if (cub->TEXTURE_WEST != NULL)
				ft_exception("Duplicated west texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->TEXTURE_WEST = ft_strdup(line);
		}
		else if (*line == 'E' && *(line + 1) == 'A' && ft_isspace(*(line + 2)))
		{
			if (cub->TEXTURE_EAST != NULL)
				ft_exception("Duplicated east texture");
			line += 2;
			while (ft_isspace(*line))
				line++;
			cub->TEXTURE_EAST = ft_strdup(line);
		}
		else if (*line == 'S' && ft_isspace(*(line + 1)))
		{
			if (cub->TEXTURE_SPRITE != NULL)
				ft_exception("Duplicated sprite texture");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->TEXTURE_SPRITE = ft_strdup(line);
		}
		else if (*line == 'F' && ft_isspace(*(line + 1)))
		{
			if (cub->FLOOR_COLOR[0] != -1 && cub->FLOOR_COLOR[1] != -1 && cub->FLOOR_COLOR[2] != -1)
				ft_exception("Duplicated floor color");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->FLOOR_COLOR[0] = ft_atoi(line);
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
			cub->FLOOR_COLOR[1] = ft_atoi(line);
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
			cub->FLOOR_COLOR[2] = ft_atoi(line);
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			if (cub->CEILING_COLOR[0] != -1 && cub->CEILING_COLOR[1] != -1 && cub->CEILING_COLOR[2] != -1)
				ft_exception("Duplicated ceiling color");
			line++;
			while (ft_isspace(*line))
				line++;
			cub->CEILING_COLOR[0] = ft_atoi(line);
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
			cub->CEILING_COLOR[1] = ft_atoi(line);
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
			cub->CEILING_COLOR[2] = ft_atoi(line);
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

void ft_parseFileCub(int fd, t_cub *cub)
{
	t_list *list_map;
	t_list *list_map_temp;
	int i;

	list_map = NULL;
	ft_parseFileCub_bis(fd, cub, &list_map);
	cub->MAP_HEIGHT = ft_lstsize(list_map);
	if ((cub->MAP = (char **)malloc((cub->MAP_HEIGHT + 1) * sizeof(char *))) == NULL)
		ft_exception("Malloc fail during map creation (step 1)");
	cub->MAP_WIDTH = ft_mapmaxwidth(list_map);
	i = 0;
	list_map_temp = list_map;
	while (list_map)
	{
		if ((cub->MAP[i] = ft_strndupfill(list_map->content, cub->MAP_WIDTH, ' ')) == NULL)
			ft_exception("Malloc fail during map creation (step 2)");
		list_map = list_map->next;
		i++;
	}
	cub->MAP[i] = NULL;
	ft_lstclear(&list_map_temp, free);
	ft_controlErrorCub(cub);
}

void ft_printCub(t_cub cub)
{
	ft_printf("RESOLUTION_X: %d  RESOLUTION_Y: %d\n", cub.RESOLUTION_X, cub.RESOLUTION_Y);
	ft_printf("TEXTURE_NORTH: %s\n", cub.TEXTURE_NORTH);
	ft_printf("TEXTURE_SOUTH: %s\n", cub.TEXTURE_SOUTH);
	ft_printf("TEXTURE_WEST: %s\n", cub.TEXTURE_WEST);
	ft_printf("TEXTURE_EAST: %s\n", cub.TEXTURE_EAST);
	ft_printf("TEXTURE_SPRITE: %s\n", cub.TEXTURE_SPRITE);
	ft_printf("FLOOR_COLOR [R: %d, G: %d, B: %d]\n", cub.FLOOR_COLOR[0], cub.FLOOR_COLOR[1], cub.FLOOR_COLOR[2]);
	ft_printf("CEILING_COLOR [R: %d, G: %d, B: %d]\n", cub.CEILING_COLOR[0], cub.CEILING_COLOR[1], cub.CEILING_COLOR[2]);
	ft_printf("MAP_SIZE [WIDTH: %d, HEIGHT: %d]\n", cub.MAP_WIDTH, cub.MAP_HEIGHT);
	ft_printf("START PLAYER [X: %d, Y: %d, DIR: %c]\n", cub.START_X, cub.START_Y, cub.START_DIR);
	ft_printf("MAP:\n");
	while (*cub.MAP)
		ft_printf("--> %s\n", *cub.MAP++);
}

int main(int argc, char **argv)
{
	if (argc == 1)
		ft_exception("No map send");
	int fd = open(argv[1], O_RDONLY);
	t_cub cub;
	ft_initCub(&cub);
	ft_parseFileCub(fd, &cub);
	close(fd);

	ft_printCub(cub);

	/*FINE*/
	ft_freecub(&cub);
}