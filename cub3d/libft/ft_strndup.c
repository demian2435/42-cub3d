/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 09:43:32 by d2435             #+#    #+#             */
/*   Updated: 2021/02/02 09:53:40 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	char	*p;
	size_t	size;

	size = n > ft_strlen(s) ? ft_strlen(s) : n;
	if ((dup = (char *)malloc((size + 1) * sizeof(char))) == NULL)
		return (NULL);
	p = dup;
	while (n && *s)
	{
		*p++ = *s++;
		n--;
	}
	*p = 0;
	return (dup);
}
