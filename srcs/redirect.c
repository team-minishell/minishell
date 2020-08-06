#include "minishell.h"

#define RIGHT_ARROW 1
#define LEFT_ARROW 2
#define DOUBLE_ARROW 3

int		execute_redirect(t_job *job, char **split)
{
	int		fd;

	if (job->redirect.sign == RIGHT_ARROW || job->redirect.sign == LEFT_ARROW)
		fd = open(job->redirect.filepath, O_RDWR | O_CREAT);
	else if (job->redirect.sign == DOUBLE_ARROW)
		fd = open(job->redirect.filepath, O_RDWR | O_CREAT | O_APPEND);
	job->redirect.save_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	// 함수 싫행부분
	dup2(job->redirect.save_fd, STDOUT_FILENO);
	return (0);
}

int		redirect_parsing(t_job *job)
{
	int		i;
	char	*tmp;
	char	**split;

	if (job->redirect.sign == RIGHT_ARROW)
		split = ft_split(job->str, '>');
	else if (job->redirect.sign == LEFT_ARROW)
		split = ft_split(job->str, '<');
	else if (job->redirect.sign == DOUBLE_ARROW)
		; //미정
	i = -1;
	while (split[++i])
	{
		tmp = split[i];
		split[i] = ft_strtrim(split[i], " ");
		free(tmp);
	}
	job->redirect.filepath = ft_strdup(split[i - 1]);
	execute_redirect(job, split);
	ft_split_del(split);
	return (0);
}

int		check_redirect(t_job *job)
{
	char	*str;
	int		i;

	str = job->str;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '<')
				job->redirect.sign = LEFT_ARROW;
			else if (str[i + 1] == '>')
				job->redirect.sign = DOUBLE_ARROW;
			else if (str[i] == '>')
				job->redirect.sign = RIGHT_ARROW;
			else
			{
				ft_printf("error\n");
				return (0);
			}
			redirect_parsing(job);
			free(job->redirect.filepath);
			return (0);
		}
		i++;
	}
	return (1);
}
