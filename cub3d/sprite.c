#include "cub3d.h"

void ft_add_sprite(t_system *sys, int x, int y)
{
	t_xy *pos = (t_xy *)malloc(sizeof(t_xy));
	pos->x = x + 0.5;
	pos->y = y + 0.5;
	ft_lstadd_back(&sys->cub.sprites, ft_lstnew(pos));
	sys->cub.map[y][x] = '0';
	sys->cub.n_sprites++;
}

void ft_sprites_calc_dist(t_list **lst, t_system *sys)
{
	t_list *start = *lst;
	while (start)
	{
		t_xy *s = (t_xy *)start->content;
		s->_x = sys->player.pos_x - s->x;
		s->_y = sys->player.pos_y - s->y;
		s->dist = sqrt(s->_x * s->_x + s->_y * s->_y);
		start = start->next;
	}
}

void ft_sprites_sort(t_list **lst)
{
	t_list *node;
	t_list *temp;
	t_xy *tempvar;

	node = *lst;
	while (node)
	{
		temp = node;
		while (temp->next)
		{
			if (((t_xy *)temp->content)->dist < ((t_xy *)temp->next->content)->dist)
			{
				tempvar = temp->content;
				temp->content = temp->next->content;
				temp->next->content = tempvar;
			}
			temp = temp->next;
		}
		node = node->next;
	}
}
