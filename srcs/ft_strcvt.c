/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcvt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 19:02:13 by hna               #+#    #+#             */
/*   Updated: 2020/07/17 19:21:28 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcvt(char *base, char *target, char *convert)
{
	int		idx;
	int		len;
	char	*temp;
	char	*ret;

	len = ft_strlen(base) - ft_strlen(target) + ft_strlen(convert) + 1;
	temp = ft_strnstr(base, target, 10);
	if (temp == 0)
		return (0);
	if (!(ret = malloc(sizeof(char) * len)))
		return (0);
	ret[0] = 0;
	idx = (int)(temp - base);
	ft_strlcat(ret, base, idx + 1);
	ft_strlcat(ret, convert, len);
	ft_strlcat(ret, &base[idx + ft_strlen(target)], len);
	return (ret);
}
