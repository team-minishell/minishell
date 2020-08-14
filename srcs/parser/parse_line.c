/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:24:00 by hna               #+#    #+#             */
/*   Updated: 2020/08/14 20:49:17 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** escape 기호 처리
*/

char		*escape_line(char *line)
{
	int		idx;
	int		i;
	char	*e_line;

	idx = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			ft_memmove(&line[i], &line[i + 1], ft_strlen(&line[i + 1]) + 1);
		}
		i++;
	}
	return (line);
}

/*
** command 구조체의 line에 파이프로 구분된 명령을 입력한다.
** 1. 파이프로 나눠서 커맨드 구조체에 입력
** 2. 리다이렉트 파싱 후 문자열 정리
** 3. argv 입력
*/

void		set_command(t_job *job)
{
	char		**splits;
	char		**cmds;
	char		*str;
	int			i;

	while (job)
	{
		if ((job->str)[0] == '\0')
		{
			job = job->next;
			continue;
		}
		make_commands(job);
		make_redirects(job);
		set_argv(job);
		job = job->next;
	}
}

/*
** 1. line을 ';'으로 구분해서 job을 나눈다.
** 2. 각 job의 redirection을 설정한다.
** 3. 각 job을 ' '로 구분해서 cmd와 argv로 구분한다.
*/

t_job		*parse_line(char *original_line)
{
	t_job		*job;
	char		*line;

	if (original_line == 0 || *original_line == 0)
		return (0);
	line = ft_strdup(original_line);
	line = escape_line(line);
	job = create_job(line);
	set_command(job);
	free(line);
	return (job);
}
