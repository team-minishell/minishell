#include "minishell.h"

// 1. 세미콜론(진행중)
// 2. 파이프
// 3. 리디렉션 (다시)
// 4. ctrl-d 누를 시 exit 출력하고 종료

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
	pid_t	pid;
	t_env	env;
	t_job	*job;
	char	*line;
	char	**tokens;

	pid = 1;
	env.envd = make_env_to_dict(envp);
	env.envp = make_dict_to_envp(env.envd);
	g_env = &env;
	clear_screen();
	handle_signal();
	while (1)
	{
		if (pid > 0)
		{
			ft_printf("\033[0;32mminishell> \033[0;0m");
			if (read_line(0, &line) == 1)
				;
			else
			{
				job = parse_line(line);
				// line = parsing(line, env.envd);
				if (job)
					execute_job(job, &env);
			}
		}
	}
	return (0);
}
