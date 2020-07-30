#include "minishell.h"

void	eof_exception(int option, char **line)
{
	if (option == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (option == 1)
	{
		ft_printf("minishell: unexpected EOF while looking for matching `\'\"\n");
		ft_printf("minishell: syntax error: unexpected end of file\n");
		free(*line);
	}
}

/*
** single quote(')와 double quote(")를 조건에 따라 열고 닫는다.
** 닫혀있음 : -1("hello world")
** 열려있음 : 1 ("hello world)
*/

void	check_quote(t_quote *q, char *line, int i)
{
	if (i == 0 && line[i] == '\"')
	{
		if (q->sq == -1)
		{
			q->dq *= -1;
		}
	}
	else if (i == 0 && line[i] == '\'')
	{
		if (q->dq == -1)
		{
			q->sq *= -1;
		}
	}
	else if (i != 0 && line[i] == '\"' && line[i - 1] != '\\')
	{
		if (q->sq == -1)
		{
			q->dq *= -1;
		}
	}
	else if (i != 0 && line[i] == '\'' && line[i - 1] != '\\')
	{
		if (q->dq == -1)
		{
			q->sq *= -1;
		}
	}
}

int		is_end_escape(char *line)
{
	int		i;

	i = 0;
	while (line[i])
		i++;
	if (i == 1 && line[i - 1] == '\\')
		return (1);
	if (i >= 2 && line[i - 1] == '\\' && line[i - 2] != '\\')
		return (1);
	return (0);
}

/*
** line을 읽어오는데 ' 나 "가 있는 경우, 줄 바꿈 문자까지 읽어온다.
*/

int		read_line2(t_quote *q, int fd, char **origin, char **new_line)
{
	int		i;
	char	*tmp;//new_line free 할때 사용하면 될듯
	char	*line;
	
	line = *origin;
	while (!(q->sq == -1 && q->dq == -1) || is_end_escape(line))
	{
		i = 0;
		ft_printf("> ");
		if (get_next_line(fd, &line) == 0)
		{
			ft_printf("minishell: unexpected EOF while looking for matching `\'\"\n");
			ft_printf("minishell: syntax error: unexpected end of file\n");
			free(line);
			return (1);
		}
		*new_line = ft_strjoin(*new_line, "\n");		//new_line free
		*new_line = ft_strjoin(*new_line, line);		//new_line free
		while (line[i])
			check_quote(q, line, i++);
		free(line);
	}
	return (0);
}

int		read_line(int fd, char **line)
{
	int		i;
	t_quote	q;
	char	*new_line;

	i = 0;
	if (get_next_line(fd, line) == 0)
	{
		ft_printf("exit\n");
		exit(0);
	}
	q.dq = -1;
	q.sq = -1;
	new_line = ft_strdup("");
	new_line = ft_strjoin(new_line, *line); // ft_strjoin_free_s1();
	while ((*line)[i])
		check_quote(&q, *line, i++);
	free(*line);
	if (read_line2(&q, fd, line, &new_line))
		return (1);
	*line = new_line;
	return (0);
}
