/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_null.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:17:06 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 10:38:19 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_pointer_null(t_flags *flags)
{
	int		count;
	char	*str;

	count = 0;
	if (!flags->point)
		str = "0x";
	else
		str = "0x0";
	if (flags->minus)
	{
		count += ft_putlstr("0x0", ft_strlen(str));
		while (count < flags->size)
			count += ft_putlchar(' ');
	}
	else
	{
		while (count < flags->size - (int)ft_strlen(str))
			count += ft_putlchar(' ');
		count += ft_putlstr("0x0", ft_strlen(str));
	}
	return (count);
}
