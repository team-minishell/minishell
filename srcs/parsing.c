/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:29:37 by hna               #+#    #+#             */
/*   Updated: 2020/07/16 22:42:01 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 입력받은 line에서 ~나 $환경변수를 치환
*/

char	*ft_strcvt(char *base_str, char *target_str, char *convert_str)
{
	int		len;
	char	*ret_str;

	len = ft_strlen(base_str);
	len = len - ft_strlen(target_str) + ft_strlen(convert_str);
	if (!(ret_str = malloc(sizeof(char) * (len + 1))))
		exit(MALLOC_ERROR);
	ret_str = ft_strnstr(base_str, target_str, ft_strlen(base_str));
	printf("%d\n", (int)(ret_str - base_str));
	return (ret_str);
}

char	*parsing(char *line, t_list *envl)
{
	int		len;
	char	*converted_line;

	converted_line = ft_strcvt("abc~~d", "~~", "hello world");
	// printf("%s\n", converted_line);
	return (0);
}