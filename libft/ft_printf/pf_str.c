/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:34:43 by marvin            #+#    #+#             */
/*   Updated: 2020/05/08 18:13:47 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*pf_strnew(size_t size)
{
	char *start;

	start = (char *)malloc((size + 1) * sizeof(*start));
	if (!start)
		return (NULL);
	pf_bzero(start, size + 1);
	return (start);
}

void	*pf_memset(void *b, int c, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}

void	pf_bzero(void *s, size_t n)
{
	pf_memset(s, 0, n);
}

int		is_nbr(const char *str, int i)
{
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	return (0);
}

int		is_specifier(const char *str, int i)
{
	if (str[i] == 'c' || str[i] == 'd' || str[i] == 's' || str[i] == 'u')
		return (1);
	if (str[i] == 'p' || str[i] == 'i' || str[i] == 'x' || str[i] == 'X')
		return (1);
	if (str[i] == '%')
		return (1);
	return (0);
}
