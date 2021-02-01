/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:36:53 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/01 17:14:49 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void					ft_clear(char *arr)
{
	int					i;

	i = 0;
	while (i < BUFFER_SIZE)
		arr[i++] = 0;
}

char					*ft_recalloc(char *line_old, ssize_t plus)
{
	char				*line_new;
	int					i;

	i = 0;
	if (!(line_new = ft_calloc(ft_strlen(line_old) + plus + 1, sizeof(char))))
		return (NULL);
	while (line_old[i])
	{
		line_new[i] = line_old[i];
		i++;
	}
	free(line_old);
	return (line_new);
}
