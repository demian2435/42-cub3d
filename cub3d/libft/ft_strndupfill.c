/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndupfill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 09:43:32 by d2435             #+#    #+#             */
/*   Updated: 2021/02/02 18:52:45 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndupfill(const char *s, size_t n, char fill)
{
	char	*dup;
	char	*p;

	if ((dup = (char *)malloc((n + 1) * sizeof(char))) == NULL)
		return (NULL);
	p = dup;
	while (n && *s)
	{
		*p++ = *s++;
		n--;
	}
	while (n)
	{
		*p++ = fill;
		n--;
	}
	*p = 0;
	return (dup);
}
