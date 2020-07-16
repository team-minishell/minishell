/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:21:39 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/27 06:16:56 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int		ft_printf(const char *format, ...)
{
	t_struct	*ptr;
	int			len;

	if (!(ptr = (t_struct *)malloc(sizeof(t_struct))))
		return (-1);
	ptr->format = format;
	ptr->len = 0;
	reset_struct(ptr);
	if (format)
	{
		va_start(ptr->ap, format);
		read_str(ptr);
		va_end(ptr->ap);
	}
	len = ptr->len;
	free(ptr);
	return (len);
}

void	reset_struct(t_struct *ptr)
{
	ptr->minus = false;
	ptr->zero = false;
	ptr->width = 0;
	ptr->dot = false;
	ptr->precision = 0;
}
