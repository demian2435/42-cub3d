/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:35:27 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/01 17:14:32 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# define MAX_FILES 4096

int		get_next_line(int fd, char **line);
char	*ft_recalloc(char *line_old, ssize_t plus);
void	ft_clear(char *arr);

#endif
