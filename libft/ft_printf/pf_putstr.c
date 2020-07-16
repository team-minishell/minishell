/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:25:04 by yochoi            #+#    #+#             */
/*   Updated: 2020/05/08 18:13:29 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void		pf_putstr(const char *s, t_struct *ptr)
{
	int i;

	i = 0;
	if (ptr->dot == false)
	{
		write(1, s, pf_strlen(s));
		ptr->len += pf_strlen(s);
	}
	else
	{
		while (i < ptr->precision && i < (int)pf_strlen(s))
		{
			pf_putchar(s[i], ptr);
			i++;
		}
	}
}

static void	zero_print(int len, t_struct *ptr)
{
	int i;

	i = 0;
	if (ptr->precision > len)
		while (i++ < (ptr->precision - len))
			pf_putchar('0', ptr);
}

void		pf_putstr_p(char *s, t_struct *ptr)
{
	int i;
	int len;

	i = 0;
	len = pf_strlen(s);
	if (ptr->dot == false)
	{
		write(1, "0x", 2);
		write(1, s, len);
		ptr->len += (2 + len);
	}
	else
	{
		write(1, "0x", 2);
		ptr->len += 2;
		if (s[0] == '0' && ptr->dot == true && ptr->precision == 0)
			return ;
		zero_print(len, ptr);
		while (i < len)
		{
			pf_putchar(s[i], ptr);
			i++;
		}
	}
}

char		*pf_strdup(char *s)
{
	char	*str;
	int		i;

	if (!(str = malloc(pf_strlen(s) + 1 * sizeof(char))))
		return (0);
	i = 0;
	while (*(s + i) != '\0')
	{
		*(str + i) = *(s + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
