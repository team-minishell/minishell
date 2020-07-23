/*#include "minishell.h"

int		check_pipe(t_job *job)
{
	int i;

	i = 0;
	while (job->str[i])
		if (job->str[i++] == '|')
			__pipe__(job);
}

// fd[0] 입구, fd[1] 출구

int		__pipe__(t_job *job)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	if ((pid = fork()) < 0)
		exit(-1);
	if (pid == 0)
	{
		close(fd[0]);
		write(fd[1], )
	}
}
*/