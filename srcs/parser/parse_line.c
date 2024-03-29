/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:24:00 by hna               #+#    #+#             */
/*   Updated: 2020/08/26 00:13:25 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			in_sq(t_quote *q)
{
	if (q->sq == 1)
		return (1);
	return (0);
}

/*
** escape 기호 처리
*/

char		*escape_line(char *line)
{
	int		i;
	t_quote	q;

	i = 0;
	init_quote(&q);
	while (line[i])
	{
		check_quote(&q, line, i);
		if (line[i] == '\\' && !in_sq(&q))
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
		else if (line[i] == '\"' && line[i + 1] == '\"')
			ft_memmove(&line[i], &line[i + 2], ft_strlen(&line[i + 2]) + 1);
		else if (line[i] == '\'' && line[i + 1] == '\'')
			ft_memmove(&line[i], &line[i + 2], ft_strlen(&line[i + 2]) + 1);
		i++;
	}
	return (line);
}

/*
** 1. ';'으로 구분된 job을 파싱
** 2. '|'으로 구분된 commands 파싱
** 3. 리디렉션 파싱
** 4. argv 파싱
*/

t_job		*parse_line(char *original_line)
{
	t_job		*job;
	t_job		*first_job;
	char		*line;

	if (original_line == 0 || *original_line == 0)
		return (0);
	line = ft_strdup(original_line);
	job = create_job(line);
	first_job = job;
	while (job)
	{
		if (job->str[0] == '\0')
		{
			job = job->next;
			continue;
		}
		make_commands(job);
		make_redirects(job);
		set_argv(job);
		job = job->next;
	}
	free(line);
	return (first_job);
}
