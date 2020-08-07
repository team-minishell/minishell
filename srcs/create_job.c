/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:37:50 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/07 19:45:04 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** job 구조체 할당 및 초기화
*/

void		init_job(t_job **job)
{
	(*job)->str = 0;
	(*job)->next = 0;
}

t_job		*malloc_job(void)
{
	t_job	*job;

	if (!(job = malloc(sizeof(t_job) * 1)))
		exit(MALLOC_ERROR);
	init_job(&job);
	return (job);
}

/*
** 세미콜론으로 구분된 명령들을 job 구조체에 담는다.
** 1. job 구조체 할당 및 초기화
** 2. ; 기준으로 split
** 3. job->str 에 세미콜론으로 구분된 명령줄을 입력, trim으로 불필요한 공백과 세미콜론 제거
*/

t_job		*create_job(char *line)
{
	t_job	*job;
	t_job	*first;
	char	**splits;
	int		i;

	i = 0;
	job = malloc_job();
	init_job(&job);
	first = job;
	splits = split_except_quote(line, ';');
	while (splits[i])
	{
		job->str = ft_strtrim(splits[i], " ;");
		if (splits[i + 1] != NULL)
			job->next = malloc_job();
		else
			job->next = NULL;
		i++;
		job = job->next;
	}
	ft_split_del(splits);
	return (first);
}
