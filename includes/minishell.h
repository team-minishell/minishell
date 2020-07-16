#ifndef MINI_SHELL
# define MINI_SHELL

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

/*
** 에러 처리
*/

# include <errno.h>
# include <string.h>

int			pwd(void);
void		read_command(char *str);
int			execution(char *str, char **envp);
void		ft_perror(char *str);

/*
** 안쓰는거
*/

typedef struct	s_shell_info
{
	char	*name;
	char	*version;
}				t_shell_info;

/*
** 명령어 저장 안쓸듯
*/

typedef struct	s_command
{
	char		*buffer;
}				t_command;

#endif