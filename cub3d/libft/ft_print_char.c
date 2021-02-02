/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:24:35 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 10:23:18 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_print_char(t_flags *flags, int c)
{
	int	count;

	count = 0;
	if (flags->minus)
	{
		count += ft_putlchar(c);
		while (flags->size > 1)
		{
			count += ft_putlchar(' ');
			flags->size -= 1;
		}
	}
	else
	{
		while (flags->size > 1)
		{
			count += ft_putlchar(' ');
			flags->size -= 1;
		}
		count += ft_putlchar(c);
	}
	return (count);
}
