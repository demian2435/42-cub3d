/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 10:23:29 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/13 14:20:10 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *nptr)
{
	long int		sum;
	int				negative;
	int				count;

	sum = 0;
	negative = 1;
	count = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			negative = -1;
	while (ft_isdigit(*nptr))
	{
		sum *= 10;
		sum += *nptr++ - '0';
		if (negative == -1 && sum < 0)
			return (0);
		if (negative == 1 && sum < 0)
			return (-1);
		count++;
	}
	if (count == 0)
		return (-1);
	return (sum * negative);
}
