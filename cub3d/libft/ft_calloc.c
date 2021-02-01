/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 10:23:46 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/18 09:43:54 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t nelem, size_t elsize)
{
	char	*p;

	if ((p = malloc(nelem * elsize)) == NULL)
		return (NULL);
	p = ft_memset(p, 0, nelem * elsize);
	return (p);
}
