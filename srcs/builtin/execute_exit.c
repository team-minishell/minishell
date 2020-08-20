/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahangyeol <nahangyeol@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:03:07 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/20 21:28:22 by nahangyeol       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_exit(t_command *command)
{
	int		i;
	int		argc;

	i = 0;
	argc = 0;
	ft_printf("exit\n");
	while (command->argv[argc])
		argc++;
	if (argc == 1)
		exit(0);
	else if (argc == 2)
	{
		while (command->argv[1][i])
		{
			if (!(ft_isdigit(command->argv[1][i])))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(command->argv[1], 2);
				ft_putstr_fd(" numeric argument required\n", 2);
				break;
			}
			i++;
		}
		g_status = ft_atoi(command->argv[1]);
		exit(ft_atoi(command->argv[1]));
	}
	ft_putstr_fd("exit: too many arguments\n", 2);
}
