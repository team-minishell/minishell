/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:23:53 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/21 23:04:16 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_screen(void)
{
	ft_printf("\ec");
	ft_printf("\e[0;34m███╗   ███╗██╗███╗   ██╗██╗███████╗\
██╗  ██╗███████╗██╗     ██╗\n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗ \n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚═════\
═╝\n\e[0;0m");
}

int		ft_perror(char *str, int err_num)
{
	char	*error_str;
	char	**split;

	if (!err_num)
		return (0);
	error_str = strerror(err_num);
	split = ft_split(error_str, ' ');
	if (!ft_strcmp(split[0], "exit"))
	{
		ft_split_del(split);
		return (-1);
	}
	ft_split_del(split);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
	return (-1);
}

void	set_envs(t_main *m, char **envp)
{
	m->env.envd = make_env_to_dict(envp);
	m->env.envp = make_dict_to_envp(m->env.envd);
	g_env = &(m->env);
}

void		test_job(t_job *job)
{
	int		i;
	int		n;
	char	**argv;
	t_redirect	*redi;

	ft_printf("========job struct test========\n");
	while (job)
	{
		i = 0;
		ft_printf("job: %p\n", job);
		ft_printf("job->str: %s$\n", job->str);
		// ft_printf("=====command=====\n");
		ft_printf("job->command->idx: %d$\n", job->command->idx);
		while (i < job->command->idx)
		{
			ft_printf("\tcommand[%d]->line : %s$\n", i, ((job->command) + i)->line);
			redi = ((job->command) + i)->redirect;
			while (redi)
			{
				ft_printf("\tredirect sign: %d\n", redi->sign);
				ft_printf("\tredirect path: %s\n", redi->filepath);
				redi = redi->next;
			}
			n = 0;
			argv = ((job->command) + i)->argv;
			while (argv[n])
			{
				ft_printf("\t\targv[%d]:%s$\n", n, argv[n]);
				n++;
			}
			i++;
		}
		job = job->next;
	}
	ft_printf("================================\n");
}

int		main(int argc, char **argv, char **envp)
{
	t_main	m;

	m.pid = 1;
	set_envs(&m, envp);
	clear_screen();
	handle_signal();
	while (1)
	{
		if (m.pid > 0)
		{
			ft_printf("\033[0;32mminishell> \033[0;0m");
			if (read_line(0, &m.line) != 1)
			{
				if (!check_syntax(m.line))
				{
					m.job = parse_line(m.line);
					if (m.job)
						execute_job(m.job);
					free_job(m.job);

				}
				free(m.line);
			}
		}
	}
	return (0);
}
