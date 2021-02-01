/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:41:19 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/18 09:44:20 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*dup;
	char	*p;

	if ((dup = malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
		return (NULL);
	p = dup;
	while (*s)
		*p++ = *s++;
	*p = 0;
	return (dup);
}
