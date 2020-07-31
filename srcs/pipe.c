#include "minishell.h"

int		check_pipe(t_job *job)
{
	int i;

	i = 0;
	while (job->str[i])
		if (job->str[i++] == '|')
			execute_pipe_command(job);
}

// fd[0] 입구, fd[1] 출구

int		execute_pipe_command(t_job *job)
{
	int		i;
	char	**split;
	char	*tmp;

	i = -1;
	split = ft_split(job->str, '|');
	while (split[++i])
	{
		tmp = split[i];
		split[i] = ft_strtrim(split[i], " ");
		free(tmp);
	}
	ft_split_del(split);
	return (0);
}
