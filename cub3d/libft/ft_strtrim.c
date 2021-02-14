/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:00:30 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/14 10:50:40 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set)
{
	int			len;
	char		*p;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_iscontain(*s1, set))
		s1++;
	len = ft_strlen(s1);
	if (!len)
		return ((char *)ft_calloc(1, 1));
	while (ft_iscontain(s1[len - 1], set))
		len--;
	if ((p = ft_strndup(s1, len)) == NULL)
		return (NULL);
	p[len] = 0;
	return (p);
}
