/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:37:35 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 02:10:19 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	tmp = *lst;
	if (!tmp || !del)
		return ;
	while (tmp)
	{
		(*del)((void *)tmp->content);
		tmp = tmp->next;
	}
	*lst = 0;
}
