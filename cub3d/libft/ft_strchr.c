/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:38:36 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/19 15:37:25 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	while (*s && (unsigned char)*s != (unsigned char)c)
		s++;
	if ((unsigned char)*s != (unsigned char)c)
		return (NULL);
	return ((char *)s);
}
