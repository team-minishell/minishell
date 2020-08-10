#include "minishell.h"

#define RIGHT_ARROW 1
#define LEFT_ARROW 2
#define DOUBLE_ARROW 3

/*int		execute_redirect(t_job *job, char **split)
{
	int		fd;

	if (job->redirect.sign == RIGHT_ARROW || job->redirect.sign == LEFT_ARROW)
		fd = open(job->redirect.filepath, O_RDWR | O_CREAT);
	else if (job->redirect.sign == DOUBLE_ARROW)
		fd = open(job->redirect.filepath, O_RDWR | O_CREAT | O_APPEND);
	job->redirect.save_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	fork_pipes(echo, hello);
	dup2(job->redirect.save_fd, STDOUT_FILENO);
	return (0);
}*/
// echo a > b.txt > c.txt
int		redirect_parsing(t_job *job)
{
	char	*str;
	int		i;
	int		j;
	char	tmp[1000];

	str = job->str;
	i = 0;
	ft_bzero(tmp, 1000);
	job->redirect = (t_redirect *)malloc(sizeof(t_redirect));
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i] == '>' && str[i + 1] == '>')
			{
				job->redirect->sign = DOUBLE_ARROW;
				i++;
			}
			else if (str[i] == '>')
				job->redirect->sign = RIGHT_ARROW;
			else if (str[i] == '<')
				job->redirect->sign = LEFT_ARROW;
			i++;
			j = 0;
			while (str[i] != '<' && str[i] != '>')
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			job->redirect->filepath = ft_strdup(tmp);
		}
		else
			i++;
	}
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
			redirect_parsing(job);
			return (0);
		}
		i++;
	}
	return (0);
}
