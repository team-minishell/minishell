/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 19:02:13 by hna               #+#    #+#             */
/*   Updated: 2020/07/17 19:48:26 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** base = 명령어
** target = 바꿔질문자 (e.g ~, $)
** convert = 바꿀문자
*/

char	*convert_str(char *base, char *target, char *convert)
{
	int		idx;
	int		len;
	char	*temp;
	char	*ret;

	len = ft_strlen(base) - ft_strlen(target) + ft_strlen(convert) + 1;
	temp = ft_strnstr(base, target, ft_strlen(base));
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
