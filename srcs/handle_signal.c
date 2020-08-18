/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 20:21:56 by yochoi            #+#    #+#             */
/*   Updated: 2020/08/17 19:57:13 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_ctrl_back_slash(int dump)
{
	(void)dump;
	ft_printf("\b \b");
	ft_printf("\b \b");
}

void	manage_ctrl_c(int dump)
{
	(void)dump;
	ft_printf("\b \b");
	ft_printf("\b \b");
	ft_printf("\n");
	ft_printf("\033[0;32mminishell> \033[0;0m");
}

int		handle_signal(void)
{
	signal(SIGINT, &manage_ctrl_c);
	signal(SIGQUIT, &manage_ctrl_back_slash);
	return (0);
}
