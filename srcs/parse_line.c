#include "minishell.h"

void		init_job(t_job **job)
{
	if (!(*job = malloc(sizeof(t_job))))
		exit(MALLOC_ERROR);
	(*job)->str = 0;
	(*job)->next = 0;
}

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

int			have_next(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (ft_isspace((int)line[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

t_job		*create_job(char *line, t_quote *q)
{
	t_job	*job;
	t_job	*first;
	int		i;
	int		start;

	i = 0;
	start = i;
	init_job(&job);
	first = job;
	while (line[i])
	{
		check_quote(q, line, i);
		if ((line[i] == ';' && is_quote_closed(q)) || line[i + 1] == '\0')
		{
			if (line[i + 1] != 0)
				line[i] = 0;
			job->str = ft_strtrim(&line[start], " ;");
			start = i + 1;
			if (have_next(&line[start]))
			{
				if (!(job->next = malloc(sizeof(t_job))))
					exit(MALLOC_ERROR);
				job = job->next;
			}
			job->next = NULL;
		}
		i++;
	}
	return (first);
}

/*
** 1. line을 ';'으로 구분해서 job을 나눈다.
** 2. 각 job의 redirection을 설정한다.
** 3. 각 job을 ' '로 구분해서 cmd와 argv로 구분한다.
*/

t_job		*parse_line(char *original_line)
{
	t_job		*job;
	t_quote		q;
	char		*line;

	ft_printf("======parse_line test======\n");
	if (original_line == 0 || *original_line == 0)
		return (0);
	line = ft_strdup(original_line);
	line = escape_line(line);
	init_quote(&q);
	// 1. ;로 job 나누기
	job = create_job(line, &q);	
	// 2. redirect
	// 3. pipe
	// 4. argv
	while (job)
	{
		ft_printf("str:%s\n", job->str);
		job = job->next;
	}
	ft_printf("=====parse_line end=====\n");
	// 2. redirection
	return (0);
}