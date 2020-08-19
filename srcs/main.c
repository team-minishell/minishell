/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:23:53 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/18 15:32:18 by nahangyeol       ###   ########.fr       */
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
	write(2, " : ", 3);
	write(2, error_str, ft_strlen(error_str));
	write(2, "\n", 1);
	return (-1);
}

void	free_command(t_job *job, int command_index)
{
	int			i;
	t_redirect	*tmp_redirect;

	i = 0;
	while (i < command_index)
	{
		free(((job->command) + i)->line);
		ft_split_del(((job->command) + i)->argv);
		while (job->command->redirect)
		{
			free(job->command->redirect->filepath);
			tmp_redirect = job->command->redirect->next;
			free(job->command->redirect);
			job->command->redirect = tmp_redirect;
		}
		i++;
	}
}

void	free_job(t_job *job)
{
	int			i;
	t_job		*tmp_job;
	int			command_index;

	i = 0;
	while (job)
	{
		command_index = job->command->idx;
		free_command(job, command_index);
		free(job->str);
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
			if (read_line(0, &m.line) != 1)
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
