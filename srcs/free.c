/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 21:14:39 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/21 19:30:15 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
