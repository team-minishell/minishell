/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 20:03:07 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/24 19:43:10 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_argument_error(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" numeric argument required\n", 2);
}

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
				print_argument_error(command->argv[1]);
				break ;
			}
			i++;
		}
		g_status = ft_atoi(command->argv[1]);
		exit(ft_atoi(command->argv[1]));
	}
	ft_putstr_fd("exit: too many arguments\n", 2);
}
