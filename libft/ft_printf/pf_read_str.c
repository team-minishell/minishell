/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 14:19:45 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:23:00 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"
#include <stdio.h>

void	read_str(t_struct *ptr)
{
	const char	*str;
	int			i;

	str = ptr->format;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			pf_putchar(str[i], ptr);
		if (str[i] == '%')
		{
			i++;
			if (!(is_specifier(str, i)))
			{
				check_flag(str, ptr, i);
				while (!(is_specifier(str, i)))
					i++;
			}
			check_format(str, ptr, i);
		}
		i++;
	}
}
