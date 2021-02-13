/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:04 by d2435             #+#    #+#             */
/*   Updated: 2021/02/13 15:48:21 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_ceiling(t_system *sys)
{
	if (sys->cub.c_rgb[0] != -1 && sys->cub.c_rgb[1] != -1 &&
		sys->cub.c_rgb[2] != -1)
		ft_exception("Duplicated ceiling color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.c_rgb[0] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	ft_skip_spaces(sys);
	if (*sys->parse.line++ != ',')
		ft_exception("Parsing ceiling color", sys);
	ft_skip_spaces(sys);
	sys->cub.c_rgb[1] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	ft_skip_spaces(sys);
	if (*sys->parse.line++ != ',')
		ft_exception("Parsing ceiling color", sys);
	ft_skip_spaces(sys);
	sys->cub.c_rgb[2] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	if (ft_skip_spaces(sys) && ft_strlen(sys->parse.line) == 0)
		sys->parse.find = 1;
	else
		ft_exception("Line ceiling wrong", sys);
}

void	ft_parse_floor(t_system *sys)
{
	if (sys->cub.f_rgb[0] != -1 && sys->cub.f_rgb[1] != -1 &&
		sys->cub.f_rgb[2] != -1)
		ft_exception("Duplicated floor color", sys);
	sys->parse.line++;
	ft_skip_spaces(sys);
	sys->cub.f_rgb[0] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	ft_skip_spaces(sys);
	if (*sys->parse.line++ != ',')
		ft_exception("Parsing floor color", sys);
	ft_skip_spaces(sys);
	sys->cub.f_rgb[1] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	ft_skip_spaces(sys);
	if (*sys->parse.line++ != ',')
		ft_exception("Parsing floor color", sys);
	ft_skip_spaces(sys);
	sys->cub.f_rgb[2] = ft_atoi(sys->parse.line);
	ft_skip_digit(sys);
	if (ft_skip_spaces(sys) && ft_strlen(sys->parse.line) == 0)
		sys->parse.find = 1;
	else
		ft_exception("Line floor wrong", sys);
}

void	ft_parse_resolution(t_system *sys)
{
	if (sys->parse.line[0] == 'R' && ft_isspace(sys->parse.line[1]) &&
		!sys->parse.find)
	{
		if (sys->cub.res_x != -1 && sys->cub.res_y != -1)
			ft_exception("Duplicated resolution", sys);
		sys->parse.line++;
		ft_skip_spaces(sys);
		sys->cub.res_x = ft_atoi(sys->parse.line);
		ft_skip_digit(sys);
		ft_skip_spaces(sys);
		sys->cub.res_y = ft_atoi(sys->parse.line);
		if (sys->cub.res_y < 100)
			ft_exception("Resolution y wrong", sys);
		if (sys->cub.res_x <= sys->cub.res_y)
			ft_exception("Wrong ratio resolution", sys);
		ft_skip_digit(sys);
		if (ft_skip_spaces(sys) && ft_strlen(sys->parse.line) == 0)
			sys->parse.find = 1;
		else
			ft_exception("Line resolution wrong", sys);
	}
}

void	ft_parse_map(int fd, t_system *sys)
{
	sys->parse.list_map = ft_lstnew(sys->parse.line);
	while ((sys->parse.count = ft_get_next_line(fd, &sys->parse.line)) > 0)
	{
		if (ft_ismap(sys->parse.line) || ft_isallspaces(sys->parse.line))
			ft_lstadd_back(&sys->parse.list_map, ft_lstnew(sys->parse.line));
		else
		{
			free(sys->parse.line);
			ft_lstclear(&sys->parse.list_map, free);
			ft_exception("Map error format", sys);
		}
	}
	if (ft_ismap(sys->parse.line) || ft_isallspaces(sys->parse.line))
		ft_lstadd_back(&sys->parse.list_map, ft_lstnew(sys->parse.line));
	else
	{
		free(sys->parse.line);
		ft_lstclear(&sys->parse.list_map, free);
		ft_exception("Map error format", sys);
	}
}

void	ft_parse_cub_bis(int fd, t_system *sys)
{
	while ((sys->parse.count = ft_get_next_line(fd, &sys->parse.line)) > 0)
	{
		sys->parse.find = 0;
		sys->parse.line_tmp = sys->parse.line;
		if (ft_isstartmap(sys->parse.line))
			return (ft_parse_map(fd, sys));
		ft_skip_spaces(sys);
		ft_parse_resolution(sys);
		ft_parse_texture_n(sys);
		ft_parse_texture_s(sys);
		ft_parse_texture_w(sys);
		ft_parse_texture_e(sys);
		ft_parse_texture_spr(sys);
		if (sys->parse.line[0] == 'F' && ft_isspace(sys->parse.line[1]) &&
			!sys->parse.find)
			ft_parse_floor(sys);
		else if (sys->parse.line[0] == 'C' && ft_isspace(sys->parse.line[1]) &&
			!sys->parse.find)
			ft_parse_ceiling(sys);
		else if (ft_skip_spaces(sys) && !sys->parse.find &&
			ft_strlen(sys->parse.line) > 0)
			ft_exception("Fake line detected", sys);
		free(sys->parse.line_tmp);
	}
}
