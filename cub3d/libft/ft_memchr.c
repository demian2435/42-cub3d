/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:27:48 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/18 09:44:13 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;

	p_s = (unsigned char *)s;
	while (n)
	{
		if (*p_s == (unsigned char)c)
			return ((void *)p_s);
		p_s++;
		n--;
	}
	return (NULL);
}
