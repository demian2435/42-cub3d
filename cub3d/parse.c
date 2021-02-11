
#include "cub3d.h"

t_list *ft_parseFileCub_bis(int fd, t_system *sys)
{
	char *line;
	char *p_line;
	int count;
	t_list *list_map;

	list_map = NULL;
	count = 0;
	while ((count = ft_get_next_line(fd, &line)) > 0)
	{
		p_line = line;
		if (ft_isstartmap(line))
		{
			if (list_map)
			{
				free(p_line);
				ft_lstclear(&list_map, free);
				ft_exception("Duplicated map", sys);
			}
			list_map = ft_lstnew(ft_strdup(line));
			free(p_line);
			while ((count = ft_get_next_line(fd, &line)) > 0)
			{
				if (ft_ismap(line))
				{
					ft_lstadd_back(&list_map, ft_lstnew(ft_strdup(line)));
					free(line);
				}
				else
					break;
			}
			if (ft_ismap(line))
			{
				ft_lstadd_back(&list_map, ft_lstnew(ft_strdup(line)));
			}
			free(line);
			return (list_map);
		}
		else if (line[0] == 'R' && ft_isspace(line[1]))
		{
			if (sys->cub.res_x != -1 && sys->cub.res_y != -1)
			{
				free(p_line);
				ft_exception("Duplicated resolution", sys);
			}
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.res_x = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.res_y = ft_atoi(line);
			free(p_line);
		}
		else if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		{
			if (sys->cub.txt_N.img != NULL)
			{
				free(p_line);
				ft_exception("Duplicated north texture", sys);
			}
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_N.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_N.width, &sys->cub.txt_N.height);
			free(p_line);
		}
		else if (*line == 'S' && *(line + 1) == 'O' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_S.img != NULL)
			{
				free(p_line);
				ft_exception("Duplicated south texture", sys);
			}
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_S.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_S.width, &sys->cub.txt_S.height);
			free(p_line);
		}
		else if (*line == 'W' && *(line + 1) == 'E' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_W.img != NULL)
			{
				free(p_line);
				ft_exception("Duplicated west texture", sys);
			}
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_W.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_W.width, &sys->cub.txt_W.height);
			free(p_line);
		}
		else if (*line == 'E' && *(line + 1) == 'A' && ft_isspace(*(line + 2)))
		{
			if (sys->cub.txt_E.img != NULL)
			{
				free(p_line);
				ft_exception("Duplicated east texture", sys);
			}
			line += 2;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_E.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_E.width, &sys->cub.txt_E.height);
			free(p_line);
		}
		else if (*line == 'S' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.txt_SPR.img != NULL)
			{
				free(p_line);
				ft_exception("Duplicated sprite texture", sys);
			}
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.txt_SPR.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx, line, &sys->cub.txt_SPR.width, &sys->cub.txt_SPR.height);
			free(p_line);
		}
		else if (*line == 'F' && ft_isspace(*(line + 1)))
		{
			if (sys->cub.f_rgb[0] != -1 && sys->cub.f_rgb[1] != -1 && sys->cub.f_rgb[2] != -1)
			{
				free(p_line);
				ft_exception("Duplicated floor color", sys);
			}
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
			{
				free(p_line);
				ft_exception("Parsing floor color", sys);
			}
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
			{
				free(p_line);
				ft_exception("Parsing floor color", sys);
			}
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.f_rgb[2] = ft_atoi(line);
			free(p_line);
		}
		else if (*line == 'C' && *(line + 1) == ' ')
		{
			if (sys->cub.c_rgb[0] != -1 && sys->cub.c_rgb[1] != -1 && sys->cub.c_rgb[2] != -1)
			{
				free(p_line);
				ft_exception("Duplicated ceiling color", sys);
			}
			line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[0] = ft_atoi(line);
			while (ft_isdigit(*line))
				line++;
			while (ft_isspace(*line))
				line++;
			if (*line != ',')
			{
				free(p_line);
				ft_exception("Parsing ceiling color", sys);
			}
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
			{
				free(p_line);
				ft_exception("Parsing ceiling color", sys);
			}
			else
				line++;
			while (ft_isspace(*line))
				line++;
			sys->cub.c_rgb[2] = ft_atoi(line);
			free(p_line);
		}
		else if (ft_ismap(line))
		{
			free(p_line);
			ft_exception("Wrong first map line", sys);
		}
		else if (ft_strlen(line) > 0)
		{
			free(p_line);
			ft_exception("Fake line detected", sys);
		}
		else
			free(p_line);
	}
	return (NULL);
}
