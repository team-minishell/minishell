/*# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>

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

int		check_pipe(t_job *job)
{
	int i;

	i = 0;
	while (job->str[i])
		if (job->str[i++] == '|')
			execute_pipe_command(job);
	return (0);
}


int		main(void)
{
	pid_t	pid;
	int		status;
	char	*argv[] = {"ls", ".", NULL};
	char	*argv2[] = {"grep", "i", NULL};
	char	*argv3[] = {"grep", "t", NULL};
	int		i = 0;
	char	*envp[] = {NULL};
	int		fd[2];
	int		ret;
	int		save_fd;

	if (pipe(fd) == -1)
	{
		write(2, "pipe error\n", 11);
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (fd[1] != 1)
		{
			save_fd = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		execve("/bin/ls", argv, envp);
	}
	waitpid(pid, &status, 0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		if (fd[0] != 0)
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		execve("/usr/bin/grep", argv2, envp);
	}
	waitpid(pid, &status, 0);
	return (0);
}
*/