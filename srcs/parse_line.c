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

/*
** set_command.c
**
** create_job 에서 생성한 job->str을 이용해서
** 1. space를 기준으로 나누고 (split)
** 2. 앞뒤 공백을 제거 (ft_strtrim)
** 3. 따옴표에 따라 환경변수를 치환 (convert_env)
** 4. 따옴표 제거 (delete_quote)
** 5. command->cmd와 command->argv에 올바른 값을 넣는다.
*/

char		*convert_env(char *str)
{
	int		i;
	char	*target;
	char	*value;
	char	*key;
	char	*ret;

	i = 0;
	ret = str;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '(')
		{
			value = find_value_in_dict(g_env->envd, &str[i + 1]);
			ft_printf("value:%s\n", value);
			target = ft_strdup(&str[i]);
			ret = convert_str(str, target, value);
			free(value);
			free(target);
			free(str);
			str = ret;
		}
		i++;
	}
	return (ret);
}

char		*delete_quote_convert_env(char *str)
{
	int		len;
	char	*temp;
	char	*key;

	if (str[0] == '\'')
	{
		len = ft_strlen(str);
		ft_memmove(str, &str[1], len);
		str[len - 2] = '\0';
		return (str);
	}
	else if (str[0] == '\"')
	{
		len = ft_strlen(str);
		ft_memmove(str, &str[1], len);
		str[len - 2] = '\0';
	}
	str = convert_env(str);
	return (str);
}

char		*ft_strtrim_free_s1(char *s1, char *set)
{
	char	*new_str;

	new_str = ft_strtrim(s1, set);
	free(s1);
	return (new_str);
}

/*
** '|'기호를 기준으로 commands를 나누고 그 갯수를 구해서 malloc한다.
*/

int			set_command_line(t_job *job, char **cmds)
{
	int		n;

	n = 0;
	while (n < job->command->idx)
	{
		((job->command) + n)->line = cmds[n];
		((job->command) + n)->redirect = 0;
		n++;
	}
	return (0);
}

int			make_commands(t_job *job)
{
	int		n;
	char	**cmds;

	cmds = split_except_quote(job->str, '|');
	n = 0;
	while (cmds[n])
	{
		cmds[n] = ft_strtrim_free_s1(cmds[n], " |");
		n++;
	}
	job->command = malloc(sizeof(t_command) * n);
	job->command->idx = n;
	set_command_line(job, cmds);
	free(cmds);
	return (0);
}

int			set_argv(t_job *job)
{
	int		i;
	int		n;
	char	**splits;

	n = 0;
	while (n < job->command->idx)
	{
		i = 0;
		splits = split_except_quote(((job->command) + n)->line, ' ');
		while (splits[i])
		{
			splits[i] = ft_strtrim_free_s1(splits[i], " ");
			splits[i] = delete_quote_convert_env(splits[i]);
			i++;
		}
		((job->command) + n)->cmd = splits[0];
		((job->command) + n)->argv = splits;
		n++;
	}
	return (0);
}

void		init_quote(t_quote *q)
{
	q->sq = -1;
	q->dq = -1;
}

int			is_quote_closed(t_quote *q)
{
	if (q->sq == -1 && q->dq == -1)
		return (1);
	return (0);
}

char		*parse_path(char *str)
{
	int		i;
	char	*ret;
	t_quote		q;

	i = 0;
	init_quote(&q);
	ret = str;
	while (str[i])
	{
		check_quote(&q, str, i);
		if ((str[i] == '>' || str[i] == '<') && is_quote_closed(&q))
		{
			ret = ft_strdup(str);
			ft_strlcat(ret, str, i);
			// ret = ft_strtrim_free_s1(ret, ">< ");
		}
		i++;
	}
	return (ret);
}

int			make_redirects(t_job *job)
{
	int			i;
	int			n;
	t_quote		q;
	t_command	*command;
	t_redirect	*redirect;
	t_redirect	*first;
	char		*str;
	int			new;

	n = 0;
	while (n < job->command->idx)
	{
		first = 0;
		i = 0;
		command = (job->command) + n;
		new = 1;
		str = command->line;
		init_quote(&q);
		while (str[i])
		{
			check_quote(&q, str, i);
			if (str[i] == '>' && str[i + 1] == '>' && is_quote_closed(&q))
			{
				if (new)
				{
					command->redirect = malloc(sizeof(t_redirect));
					first = command->redirect;
					new = 0;
				}
				else
				{
					command->redirect->next = malloc(sizeof(t_redirect));
					command->redirect = command->redirect->next;
				}
				command->redirect->filepath = parse_path(&str[i + 2]);
				command->redirect->sign = DOUBLE_ARROW;
				command->redirect->next = 0;
				i++;
			}
			else if (str[i] == '>' && is_quote_closed(&q))
			{
				if (new)
				{
					command->redirect = malloc(sizeof(t_redirect));
					first = command->redirect;
					new = 0;
				}
				else
				{
					command->redirect->next = malloc(sizeof(t_redirect));
					command->redirect = command->redirect->next;
				}
				command->redirect->filepath = parse_path(&str[i + 1]);
				command->redirect->sign = RIGHT_ARROW;
				command->redirect->next = 0;
			}
			else if (str[i] == '<' && is_quote_closed(&q))
			{
				if (new)
				{
					command->redirect = malloc(sizeof(t_redirect));
					first = command->redirect;
					new = 0;
				}
				else
				{
					command->redirect->next = malloc(sizeof(t_redirect));
					command->redirect = command->redirect->next;
				}
				command->redirect->filepath = parse_path(&str[i + 1]);
				command->redirect->sign = LEFT_ARROW;
				command->redirect->next = 0;
			}
			i++;
		}
		command->redirect = first;
		n++;
	}
	return (0);
}

/*
** command 구조체의 line에 파이프로 구분된 명령을 입력한다.
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
		// 1. 파이프 나누기
		// 2. 파이프 개수 파악
		// 3. command malloc
		// 4. 분리 후 각각 argv화

		make_commands(job);
		make_redirects(job);
		set_argv(job);
		job = job->next;
	}
}

void		test_job(t_job *job)
{
	int		i;
	int		n;
	char	**argv;

	ft_printf("========job struct test========\n");
	while (job)
	{
		i = 0;
		ft_printf("job: %p\n", job);
		ft_printf("job->str: %s$\n", job->str);
		// ft_printf("=====command=====\n");
		ft_printf("job->command->idx: %d$\n", job->command->idx);
		while (i < job->command->idx)
		{
			ft_printf("\tcommand[%d]->line : %s$\n", i, ((job->command) + i)->line);
			while (((job->command) + i)->redirect)
			{
				ft_printf("\tredirect sign: %d\n", ((job->command) + i)->redirect->sign);
				ft_printf("\tredirect path: %s\n", ((job->command) + i)->redirect->filepath);
				((job->command) + i)->redirect = ((job->command) + i)->redirect->next;
			}
			n = 0;
			argv = ((job->command) + i)->argv;
			while (argv[n])
			{
				ft_printf("\t\targv[%d]:%s$\n", n, argv[n]);
				n++;
			}
			i++;
		}
		job = job->next;
	}
	ft_printf("================================\n");
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

	// ft_printf("parse_line start\n");
	if (original_line == 0 || *original_line == 0)
	//{
	//	ft_printf("input line empty\n");
		return (0);
	//}
	// ft_printf("ft_strdup\n");
	line = ft_strdup(original_line);
	// ft_printf("escape_line\n");
	line = escape_line(line);
	// ft_printf("create_job\n");
	job = create_job(line);
	// ft_printf("set command\n");
	set_command(job); // make pipe
	// create_redirect(job);
	test_job(job);
	// ft_printf("parse_line end\n");
	free(line);
	return (job);
}
