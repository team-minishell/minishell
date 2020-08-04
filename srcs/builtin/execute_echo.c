/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochoi <yochoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 20:35:08 by yochoi            #+#    #+#             */
/*   Updated: 2020/07/17 21:28:59 by yochoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_string_without_doublequote(char *string)
{
	int i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] != '\"')
			ft_putchar_fd(string[i], 1);
		i++;
	}
}

int		execute_echo(t_job *job)
{
	int i;

	if (!ft_strcmp("-n", job->command.argv[1]))
	{
		i = 2;
		while(job->command.argv[i])
		{
			print_string_without_doublequote(job->command.argv[i++]);
			if (job->command.argv[i])
				ft_printf(" ");
		}
	}
	else
	{
		i = 1;
		while(job->command.argv[i])
		{
			print_string_without_doublequote(job->command.argv[i++]);
			if (job->command.argv[i])
				ft_printf(" ");
		}
		ft_printf("\n");
	}
	return 0;
}