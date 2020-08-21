/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:24:13 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/21 21:56:03 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** line을 읽어오는데 ' 나 "가 있는 경우, 줄 바꿈 문자까지 읽어온다.
*/

int		ctrl_d(char **line)
{
	char *tmp;

	ft_printf("  \b\b");
	if (ft_strlen(*line) == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	while (get_next_line(0, &tmp) == 0)
	{
		ft_printf("  \b\b");
		free(tmp);
	}
	free(tmp);
	return (0);
}

int		multiline_eof_exception(char *line)
{
	ft_printf("minishell: unexpected EOF while looking for matching `\'\"\n");
	ft_printf("minishell: syntax error: unexpected end of file\n");
	free(line);
	return (1);
}

int		read_line2(t_quote *q, int fd, char **origin, char **new_line)
{
	int		i;
	char	*tmp;
	char	*line;

	line = *origin;
	while (!(is_quote_closed(q)))
	{
		i = 0;
		ft_printf("> ");
		if (get_next_line(fd, &line) == 0)
			if (multiline_eof_exception(line))
				return (1);
		tmp = *new_line;
		*new_line = ft_strjoin(*new_line, "\n");
		free(tmp);
		tmp = *new_line;
		*new_line = ft_strjoin(*new_line, line);
		free(tmp);
		while (line[i])
			check_quote(q, line, i++);
		free(line);
	}
	return (0);
}

int		read_line(int fd, char **line)
{
	int		i;
	char	*tmp;
	char	*new_line;
	t_quote	q;

	i = 0;
	if (get_next_line(fd, line) == 0)
		if (!ctrl_d(line))
			return (0);
	init_quote(&q);
	new_line = ft_strdup("");
	tmp = new_line;
	new_line = ft_strjoin(new_line, *line);
	free(tmp);
	while ((*line)[i])
		check_quote(&q, *line, i++);
	free(*line);
	if (read_line2(&q, fd, line, &new_line))
		return (1);
	*line = new_line;
	return (0);
}
