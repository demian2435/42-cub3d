/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:01:17 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/19 14:37:52 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	char	*p;
	size_t	size;

	size = n > ft_strlen(s) ? ft_strlen(s) : n;
	if ((dup = malloc(size + 1)) == NULL)
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

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || !len)
		return (((char *)ft_calloc(1, sizeof(char))));
	while (start && *s)
	{
		s++;
		start--;
	}
	return (ft_strndup(s, len));
}
