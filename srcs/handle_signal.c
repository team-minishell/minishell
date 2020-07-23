#include "minishell.h"

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
	signal(SIGINT, (void *)manage_ctrl_c);
	return (0);
}