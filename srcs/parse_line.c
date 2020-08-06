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

/*
** create_job.c
** 들어온 문자열을 ';' 단위로 나누어서, job->str에 저장한다.
*/

t_job		*malloc_job(void)
{
	t_job	*job;

	if (!(job = malloc(sizeof(t_job) * 1)))
		exit(MALLOC_ERROR);
	init_job(&job);
	return (job);
}

t_job		*create_job(char *line)
{
	t_job	*job;
	t_job	*first;
	char	**splits;
	int		i;

	i = 0;
	job = malloc_job();
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
	t_command	*command;
	char		**splits;
	char		*str;
	int			i;

	while (job)
	{
		command = job->command;
		if ((job->str)[0] == '\0')
		{
			job = job->next;
			continue;
		}
		splits = split_except_quote(job->str, ' ');
		i = 0;
		while (splits[i])
		{
			splits[i] = ft_strtrim_free_s1(splits[i], " ");
			splits[i] = delete_quote_convert_env(splits[i]);
			i++;
		}
		command->cmd = splits[0];
		command->argv = splits;
		job = job->next;
	}
}

/*
** set_command.c	end
*/

/*
** set_pipe.c
*/

/*
** 1. line을 ';'으로 구분해서 job을 나눈다.
** 2. 각 job의 redirection을 설정한다.
** 3. 각 job을 ' '로 구분해서 cmd와 argv로 구분한다.
*/

void		test_job(t_job *job)
{
	int		i;

	ft_printf("========job struct test========\n");
	while (job)
	{
		i = 0;
		ft_printf("job: %s$\n", job->str);
		ft_printf("cmd: %s$\n", job->command->cmd);
		while (((job->command)->argv)[i])
		{
			ft_printf("argv[%d]: %s$\n", i, ((job->command)->argv)[i]);
			i++;
		}
		job = job->next;
	}
	ft_printf("================================\n");
}

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
	//test_job(job);

	return (job);
}
