/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:22:03 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/04 02:11:13 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *ptr;

	if (!(ptr = ft_calloc(sizeof(ptr), 1)))
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
