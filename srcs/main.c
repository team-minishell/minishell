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
	env.envd = make_env_to_dict(envp);
	env.envp = make_dict_to_envp(env.envd);
	clear_screen();
	while (1)
	{
		if (pid > 0)
		{
			ft_printf("\033[0;32mminishell> \033[0;0m");
			get_next_line(0, &line);
			line = parsing(line, env.envd);
			if (line)
				execution(line, &env);
		}
	}
	free_env(&env);
	return (0);
}