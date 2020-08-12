#include "minishell.h"

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
	char	**split;

	error_str = strerror(errno);
	split = ft_split(error_str, ' ');
	if (!ft_strcmp(split[0], "exit"))
	{
		ft_split_del(split);
		return ;
	}
	ft_split_del(split);
	write(2, str, ft_strlen(str));
	write(2, " : ", 3);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
}

void	free_job(t_job *job)
{
	int			i;
	t_job		*tmp_job;
	t_redirect	*tmp_redirect;
	int			command_index;

	i = 0;
	command_index = job->command->idx;
	while (job)
	{
		free(job->str);
		while (i < command_index)
		{
			free(((job->command)+ i)->line);
			free(((job->command)+ i)->cmd);
			//ft_split_del(((job->command)+ i)->argv);
			while (job->command->redirect)
			{
				free(job->command->redirect->filepath);
				tmp_redirect = job->command->redirect->next;
				free(job->command->redirect);
				job->command->redirect = tmp_redirect;
			}
			i++;
		}
		free(job->command);
		tmp_job = job->next;
		free(job);
		job = tmp_job;
	}
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
				if (m.job)
					execute_job(m.job);
				free_job(m.job);
				free(m.line);
			}
		}
	}
	return (0);
}
