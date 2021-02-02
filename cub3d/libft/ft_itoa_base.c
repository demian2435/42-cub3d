/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:24:40 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 10:20:30 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_base_tris(int number, int base, char *arr, int count)
{
	long int	temp;
	char		*str;

	temp = (long int)number;
	if (number < 0)
		temp = temp * -1;
	if (!(str = malloc((count + 1) * sizeof(char))))
		return (NULL);
	str[count] = 0;
	while (temp > 0)
	{
		str[count - 1] = arr[temp % base];
		temp /= base;
		count--;
	}
	if (number < 0)
		str[0] = '-';
	return (str);
}

static char		*ft_itoa_base_bis(int number, int base)
{
	char		*arr;
	long int	temp;
	int			count;

	arr = "0123456789abcdef";
	count = 0;
	temp = (long int)number;
	if (number < 0)
	{
		temp = temp * -1;
		count++;
	}
	while (temp > 0)
	{
		temp /= base;
		count++;
	}
	return (ft_itoa_base_tris(number, base, arr, count));
}

char			*ft_itoa_base(int number, int base)
{
	char		*str;

	if (number == 0)
	{
		if (!(str = malloc(2 * sizeof(char))))
			return (NULL);
		str[0] = '0';
		str[1] = 0;
		return (str);
	}
	return (ft_itoa_base_bis(number, base));
}
