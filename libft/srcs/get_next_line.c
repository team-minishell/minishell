/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 14:23:18 by yochoi            #+#    #+#             */
/*   Updated: 2020/04/18 10:01:37 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stack_buff_join(char *stack, char *buff)
{
	char	*temp;

	temp = ft_strjoin(stack, buff);
	free(stack);
	free(buff);
	return (temp);
}

static char	*update_line(char *stack, int ret)
{
	char	*line;
	int		i;

	line = 0;
	i = 0;
	if (ret == 0)
		line = ft_strdup(stack);
	else if (ret > 0)
	{
		while (stack[i] != '\n')
			i++;
		line = ft_substr(stack, 0, i);
	}
	return (line);
}

static char	*update_stack(char *stack, int ret)
{
	int		i;
	char	*temp;

	temp = 0;
	i = 0;
	if (ret > 0)
	{
		while (stack[i] != '\n')
			i++;
		temp = ft_strdup(stack + i + 1);
	}
	free(stack);
	stack = NULL;
	return (temp);
}

int			get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	int			ret;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	ret = 1;
	if (stack[fd] == 0)
		stack[fd] = ft_strdup("");
	while (ft_strchr(stack[fd], '\n') == 0 && ret > 0)
	{
		if (!(buff = ft_calloc(1, BUFFER_SIZE + 1)) ||
				(ret = read(fd, buff, BUFFER_SIZE)) < 0)
			return (-1);
		stack[fd] = stack_buff_join(stack[fd], buff);
	}
	*line = update_line(stack[fd], ret);
	stack[fd] = update_stack(stack[fd], ret);
	return (ret > 0 ? 1 : ret);
}
