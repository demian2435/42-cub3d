#include "cub3d.h"

void ft_parse_ceiling(t_system *sys)
{
	if (sys->cub.c_rgb[0] != -1 && sys->cub.c_rgb[1] != -1 && sys->cub.c_rgb[2] != -1)
		ft_exception("Duplicated ceiling color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.c_rgb[0] = ft_atoi(sys->parse.line);
	while (ft_isdigit(*sys->parse.line))
		sys->parse.line++;
	ft_skip_spaces(sys);
	if (*sys->parse.line != ',')
		ft_exception("Parsing ceiling color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.c_rgb[1] = ft_atoi(sys->parse.line);
	while (ft_isdigit(*sys->parse.line))
		sys->parse.line++;
	ft_skip_spaces(sys);
	if (*sys->parse.line != ',')
		ft_exception("Parsing ceiling color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.c_rgb[2] = ft_atoi(sys->parse.line);
}

void ft_parse_floor(t_system *sys)
{
	if (sys->cub.f_rgb[0] != -1 && sys->cub.f_rgb[1] != -1 && sys->cub.f_rgb[2] != -1)
		ft_exception("Duplicated floor color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.f_rgb[0] = ft_atoi(sys->parse.line);
	while (ft_isdigit(*sys->parse.line))
		sys->parse.line++;
	ft_skip_spaces(sys);
	if (*sys->parse.line != ',')
		ft_exception("Parsing floor color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.f_rgb[1] = ft_atoi(sys->parse.line);
	while (ft_isdigit(*sys->parse.line))
		sys->parse.line++;
	ft_skip_spaces(sys);
	if (*sys->parse.line != ',')
		ft_exception("Parsing floor color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.f_rgb[2] = ft_atoi(sys->parse.line);
}

void ft_parse_resolution(t_system *sys)
{
	if (sys->cub.res_x != -1 && sys->cub.res_y != -1)
		ft_exception("Duplicated resolution", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.res_x = ft_atoi(sys->parse.line);
	while (ft_isdigit(*sys->parse.line))
		sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.res_y = ft_atoi(sys->parse.line);
}

void ft_parse_map(int fd, t_system *sys)
{
	sys->parse.list_map = ft_lstnew(sys->parse.line);
	while ((sys->parse.count = ft_get_next_line(fd, &sys->parse.line)) > 0)
	{
		if (ft_ismap(sys->parse.line))
			ft_lstadd_back(&sys->parse.list_map, ft_lstnew(sys->parse.line));
		else
			break;
	}
	if (ft_ismap(sys->parse.line))
		ft_lstadd_back(&sys->parse.list_map, ft_lstnew(sys->parse.line));
	else
		free(sys->parse.line);
}

void ft_parseFileCub_bis(int fd, t_system *sys)
{
	while ((sys->parse.count = ft_get_next_line(fd, &sys->parse.line)) > 0)
	{
		sys->parse.line_tmp = sys->parse.line;
		if (ft_isstartmap(sys->parse.line))
			return (ft_parse_map(fd, sys));
		else if (sys->parse.line[0] == 'R' && ft_isspace(sys->parse.line[1]))
			ft_parse_resolution(sys);
		else if (sys->parse.line[0] == 'N' && sys->parse.line[1] == 'O' && ft_isspace(sys->parse.line[2]))
			ft_parse_texture_N(sys);
		else if (sys->parse.line[0] == 'S' && sys->parse.line[1] == 'O' && ft_isspace(sys->parse.line[2]))
			ft_parse_texture_S(sys);
		else if (sys->parse.line[0] == 'W' && sys->parse.line[1] == 'E' && ft_isspace(sys->parse.line[2]))
			ft_parse_texture_W(sys);
		else if (sys->parse.line[0] == 'E' && sys->parse.line[1] == 'A' && ft_isspace(sys->parse.line[2]))
			ft_parse_texture_E(sys);
		else if (sys->parse.line[0] == 'S' && ft_isspace(sys->parse.line[1]))
			ft_parse_texture_spr(sys);
		else if (sys->parse.line[0] == 'F' && ft_isspace(sys->parse.line[1]))
			ft_parse_floor(sys);
		else if (sys->parse.line[0] == 'C' && ft_isspace(sys->parse.line[1]))
			ft_parse_ceiling(sys);
		else if (ft_strlen(sys->parse.line) > 0)
			ft_exception("Fake line detected", sys);
		free(sys->parse.line_tmp);
	}
}