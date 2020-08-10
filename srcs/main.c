#include "minishell.h"

// 1. 세미콜론(진행중)
// 2. 파이프
// 3. 리디렉션 (다시)
// 4. ctrl-d 누를 시 exit 출력하고 종료

void	clear_screen(void)
{
	ft_printf ("\ec");
	ft_printf("\e[0;34m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\e[0;0m");
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
	t_main	m;

	m.pid = 1;
	m.env.envd = make_env_to_dict(envp);
	m.env.envp = make_dict_to_envp(m.env.envd);
	g_env = &m.env;
	clear_screen();
	handle_signal();
	while (1)
	{
		if (m.pid > 0)
		{
			ft_printf("\033[0;32mminishell> \033[0;0m");
			if (read_line(0, &m.line) == 1)
				;
			else
			{
				m.job = parse_line(m.line);
				// line = parsing(line, env.envd);
				if (m.job)
					execute_job(m.job);
				free(m.job);
			}
		}
	}
	return (0);
}
