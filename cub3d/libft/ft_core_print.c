/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:24:51 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 10:13:11 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_core_print(char *str, t_flags *flags, va_list *args)
{
	if (*str == 'c')
		return (ft_print_char(flags, va_arg(*args, int)));
	else if (*str == 's')
		return (ft_print_string(flags, va_arg(*args, char *)));
	else if (*str == 'p')
		return (ft_print_pointer(flags, va_arg(*args, size_t)));
	else if (*str == 'd' || *str == 'i')
		return (ft_print_decimal(flags, va_arg(*args, ssize_t)));
	else if (*str == 'u')
		return (ft_print_decimal_unsigned(flags, va_arg(*args, size_t)));
	else if (*str == 'x')
		return (ft_print_exa(flags, va_arg(*args, size_t), 0));
	else if (*str == 'X')
		return (ft_print_exa(flags, va_arg(*args, size_t), 1));
	else if (*str == '%')
		return (ft_print_percent(flags));
	return (-1);
}
