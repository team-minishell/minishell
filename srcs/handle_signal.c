#include "minishell.h"

void	manage_ctrl_back_slash(int _)
{
	(void)_;
	ft_printf("\b \b");
	ft_printf("\b \b");
}

void	manage_ctrl_c(int _)
{
	(void)_;
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