/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 00:59:15 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 03:02:38 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}
