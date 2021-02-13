/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 23:27:09 by d2435             #+#    #+#             */
/*   Updated: 2021/02/13 15:13:55 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_texture_n(t_system *sys)
{
	char *tmp;

	if (sys->parse.line[0] == 'N' && sys->parse.line[1] == 'O' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_n.img != NULL)
			ft_exception("Duplicated north texture", sys);
		sys->parse.line += 2;
		tmp = ft_strtrim(sys->parse.line, " \t\f\r\v");
		if (ft_istypefile(tmp, ".xpm"))
			sys->cub.txt_n.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				tmp, &sys->cub.txt_n.width, &sys->cub.txt_n.height);
		else if (ft_istypefile(tmp, ".png"))
			sys->cub.txt_n.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				"../textures/cave.xpm", &sys->cub.txt_n.width,
				&sys->cub.txt_n.height);
		free(tmp);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_s(t_system *sys)
{
	char *tmp;

	if (sys->parse.line[0] == 'S' && sys->parse.line[1] == 'O' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_s.img != NULL)
			ft_exception("Duplicated south texture", sys);
		sys->parse.line += 2;
		tmp = ft_strtrim(sys->parse.line, " \t\f\r\v");
		if (ft_istypefile(tmp, ".xpm"))
			sys->cub.txt_s.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				tmp, &sys->cub.txt_s.width, &sys->cub.txt_s.height);
		else if (ft_istypefile(tmp, ".png"))
			sys->cub.txt_s.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				"../textures/cave.xpm", &sys->cub.txt_n.width,
				&sys->cub.txt_n.height);
		free(tmp);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_w(t_system *sys)
{
	char *tmp;

	if (sys->parse.line[0] == 'W' && sys->parse.line[1] == 'E' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_w.img != NULL)
			ft_exception("Duplicated west texture", sys);
		sys->parse.line += 2;
		tmp = ft_strtrim(sys->parse.line, " \t\f\r\v");
		if (ft_istypefile(tmp, ".xpm"))
			sys->cub.txt_w.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				tmp, &sys->cub.txt_w.width, &sys->cub.txt_w.height);
		else if (ft_istypefile(tmp, ".png"))
			sys->cub.txt_w.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				"../textures/cave.xpm", &sys->cub.txt_n.width,
				&sys->cub.txt_n.height);
		free(tmp);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_e(t_system *sys)
{
	char *tmp;

	if (sys->parse.line[0] == 'E' && sys->parse.line[1] == 'A' &&
		ft_isspace(sys->parse.line[2]) && !sys->parse.find)
	{
		if (sys->cub.txt_e.img != NULL)
			ft_exception("Duplicated east texture", sys);
		sys->parse.line += 2;
		tmp = ft_strtrim(sys->parse.line, " \t\f\r\v");
		if (ft_istypefile(tmp, ".xpm"))
			sys->cub.txt_e.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				tmp, &sys->cub.txt_e.width, &sys->cub.txt_e.height);
		else if (ft_istypefile(tmp, ".png"))
			sys->cub.txt_e.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				"../textures/cave.xpm", &sys->cub.txt_n.width,
				&sys->cub.txt_n.height);
		free(tmp);
		sys->parse.find = 1;
	}
}

void	ft_parse_texture_spr(t_system *sys)
{
	char *tmp;

	if (sys->parse.line[0] == 'S' && ft_isspace(sys->parse.line[1]) &&
		!sys->parse.find)
	{
		if (sys->cub.txt_spr.img != NULL)
			ft_exception("Duplicated sprite texture", sys);
		sys->parse.line++;
		tmp = ft_strtrim(sys->parse.line, " \t\f\r\v");
		if (ft_istypefile(tmp, ".xpm"))
			sys->cub.txt_spr.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				tmp, &sys->cub.txt_spr.width,
				&sys->cub.txt_spr.height);
		else if (ft_istypefile(tmp, ".png"))
			sys->cub.txt_spr.img = mlx_xpm_file_to_image(sys->mlx_vars.mlx,
				"../textures/cave.xpm", &sys->cub.txt_n.width,
				&sys->cub.txt_n.height);
		free(tmp);
		sys->parse.find = 1;
	}
}
