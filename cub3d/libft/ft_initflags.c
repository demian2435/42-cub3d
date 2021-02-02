/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initflags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 10:24:46 by dmalori           #+#    #+#             */
/*   Updated: 2021/02/02 10:16:10 by d2435            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_flags		ft_initflags(t_flags flags)
{
	flags.minus = 0;
	flags.point = -1;
	flags.size = 0;
	flags.terminator = 0;
	flags.zero = 0;
	return (flags);
}
