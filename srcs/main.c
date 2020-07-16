#include "minishell.h"

void	ft_perror(char *str)
{
	char	*error_str;

	error_str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, " : ", 3);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}

int		pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	ft_printf("%s\n", buf);
	return (1);
}

int		execution(char *str)
{
	pid_t	pid;
	char	**tokens;
	int		status;
	char	**envp = {NULL};

	tokens = ft_split(str, ' ');
	pid = fork();
	if (pid == 0)
	{
		execve(tokens[0], tokens, envp);
		if (errno)
			ft_perror(tokens[0]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	int		status;
	int		pid;
	char	*line;
	char	**tokens;

	pid = 1;
	while (1)
	{
		if (pid > 0)
		{
			ft_printf("minishell> ");
			get_next_line(0, &line);
			execution(line);
		}
		/*
			2. 적절하게 구분하기
		
		tokens = ft_split(line, ' ');
		*/

		/*
			3. 순차적으로 실행하기
		
		if (ft_strcmp(tokens[0], "echo") == 0)
		{
			ft_printf("%s\n", tokens[1]);
			free(tokens[0]);
			free(tokens[1]);
			free(tokens);
		}
		*/
		/*
		if (pid == 0)
		{
			char	*argv[2];
			char	*envp[] = {NULL};
			argv[0] = ft_strdup(line);
			argv[1] = 0;
			execve(line, argv, envp);
			if (errno)
				ft_perror("execve");
			exit(0);
		}
		ft_printf("pid:%d\n", pid);
		waitpid(pid, &status, 0);
		*/
		/*
			4. 에러처리하기.
		*/
	}
	return (0);
}