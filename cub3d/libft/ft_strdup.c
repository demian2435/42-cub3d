/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:41:19 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 09:53:09 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*dup;
	char	*p;

	if ((dup = malloc((ft_strlen(s) + 1) * sizeof(char))) == NULL)
		return (NULL);
	p = dup;
	while (*s)
		*p++ = *s++;
	*p = 0;
	return (dup);
}