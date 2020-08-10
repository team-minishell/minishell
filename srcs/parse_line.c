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
		// set_pipe();
		cmds = split_except_quote(job->str, '|');
		int		n;
		n = 0;
		while (cmds[n])
		{
			cmds[n] = ft_strtrim_free_s1(cmds[n], " |");
			n++;
		}
		job->command = malloc(sizeof(t_command) * n);
		job->command->idx = n;
		// set_argv(idx, cmds);
		n = 0;
		while (n < job->command->idx)
		{
			i = 0;
			splits = split_except_quote(cmds[n], ' ');
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
		ft_printf("job: %s$\n", job->str);
		// ft_printf("=====command=====\n");
		ft_printf("job->command->idx: %d$\n", job->command->idx);
		while (i < job->command->idx)
		{
			ft_printf("\tcommand[%d]\n", i);
			n = 0;
			argv = ((job->command) + i)->argv;
			while (argv[n])
			{
				ft_printf("\t\targv[%d]:%s$\n", n, argv[n]);
				n++;
			}
			i++;
		}
		// ft_printf("cmd: %s$\n", ((job->command) + i)->cmd);
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

	if (original_line == 0 || *original_line == 0)
		return (0);
	line = ft_strdup(original_line);
	line = escape_line(line);
	job = create_job(line);
	// set_pipe;
	// set_redirect;
	set_command(job);
	test_job(job);

	return (job);
}
