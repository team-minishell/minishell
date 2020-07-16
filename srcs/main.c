#include "minishell.h"

void	clear_screen(void)
{
	ft_printf ("\ec");
	ft_printf("\e[0;34m __   __  ___   __    _  ___   _______  __   __  _______  ___      ___     \n \
|  |_|  ||   | |  |  | ||   | |       ||  | |  ||       ||   |    |   |    \n \
|       ||   | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |    \n \
|       ||   | |       ||   | | |_____ |       ||   |___ |   |    |   |    \n \
|       ||   | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___ \n \
| ||_|| ||   | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |\n \
|_|   |_||___| |_|  |__||___| |_______||__| |__||_______||_______||_______|\n\e[0;0m");
}

void	ft_perror(char *str)
{
	char	*error_str;

	error_str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, " : ", 3);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	int		status;
	int		pid;
	char	*line;
	char	**tokens;

	pid = 1;
	env.envl = make_env_to_list(envp);
	env.envp = make_list_to_envp(env.envl);
	clear_screen();
	while (1)
	{
		if (pid > 0)
		{
			ft_printf("\033[0;32mminishell> \033[0;0m");
			get_next_line(0, &line);
			// parsing(line, env.envl);// 아무것도 안쳤을때 예외 추가해야함
			execution(line, &env);
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