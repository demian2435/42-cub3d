/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalori <dmalori@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:26:10 by dmalori           #+#    #+#             */
/*   Updated: 2021/01/18 09:44:08 by dmalori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*new_ele;

	if ((new_ele = malloc(sizeof(t_list))) == NULL)
		return (NULL);
	new_ele->content = content;
	new_ele->next = NULL;
	return (new_ele);
}
