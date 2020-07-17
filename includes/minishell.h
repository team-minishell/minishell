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

typedef struct		s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
	
}					t_dict;


typedef struct		s_env
{
	char			**envp;
	t_dict			*envd;
}					t_env;


int					execute_pwd(char **tokens);
int					execute_cd(char **tokens, t_env *env);
int					execute_env(char **tokens, t_env *env);

t_list				*make_env_to_dict(char **envp);
char				**make_dict_to_envp(t_list *envl);

void				read_command(char *str);
int					execution(char *str, t_env *env);

void				ft_perror(char *str);

int					check_builtins(char **tokens, t_env *env);


char				*parsing(char *line, t_list *envl);

char				*convert_str(char *base, char *target, char *convert);

#endif