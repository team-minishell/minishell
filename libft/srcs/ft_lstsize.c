/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 00:20:49 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 02:39:17 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		size;

	size = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
