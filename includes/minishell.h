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

# define MALLOC_ERROR 100

typedef struct	s_env
{
	char		**envp;
	t_list		*envl;
}				t_env;

/*
** builtin_pwd.c
*/

int			execute_pwd(char **tokens);

/*
** builtin_cd.c
*/

int			execute_cd(char **tokens);

/*
** make_env_to_list.c
*/

t_list		*make_env_to_list(char **envp);
char		**make_list_to_envp(t_list *envl);

/*
** read_command.c
*/

void		read_command(char *str);
int			execution(char *str, t_env *env);

/*
** main.c
*/

void		ft_perror(char *str);

/*
** check_builtins.c
*/

int			check_builtins(char **tokens, t_env *env);

/*
** parsing.c
*/

char	*parsing(char *line, t_list *envl);

/*
** ft_strcvt.c
*/

char	*ft_strcvt(char *base, char *target, char *convert);

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