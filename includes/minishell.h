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

# define MALLOC_ERROR	100
# define KEY_LEFT		0x0107
# define KEY_RIGHT		0x0108

typedef struct		s_redirect
{
	char				*sign; // > < >>
	int					save_fd; // fd 원상복구를 위한 저장본
	char				*filepath; // 목표지점
	struct s_redirect	*next; // 다음 리디렉션
}					t_redirect;

typedef struct		s_command
{
	char			*cmd; //명령어
	char			**argv; //인자
	int				idx; //모름
}					t_command;

typedef struct		s_job
{
	char			*str; //세미콜론으로 구분된 하나의 문자열
	t_command		command;
	t_redirect		redirect;
	struct s_job	*next; //다음 문자열
}					t_job;

typedef struct	s_quote
{
	int		sq;
	int		dq;
}				t_quote;

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

t_env				*g_env;

/*
** check_builtins.c
*/

int					check_builtins(char **tokens, t_env *env);

/*
** convert_str.c
*/

char				*convert_str(char *base, char *target, char *convert);

/*
** execute_cd.c
*/

int					execute_cd(char **tokens, t_env *env);

/*
** execute_echo.c
*/

int					execute_echo(char **tokens);

/*
** execute_env.c
*/

int					execute_env(char **tokens, t_env *env);

/*
** execute_export.c
*/

int					execute_export(char **tokens, t_env *env);

/*
** execute_pwd.c
*/

int					execute_pwd(char **tokens);

/*
** execute_unset.c
*/

int					execute_unset(char **tokens, t_env *env);

/*
** execution.c
*/

int					execution(char *str, t_env *env);
void				execute_job(t_job *job, t_env *env);

/*
** handle_signal.c
*/

int					handle_signal(void);

/*
** main.c
*/

void				ft_perror(char *str);

/*
** manage_list.c
*/

int					dict_size(t_dict *dict);
t_dict				*make_env_to_dict(char **envp);
char				**make_dict_to_envp(t_dict *envd);
t_dict				*find_env(t_dict *envd, char *key);
char				*find_value_in_dict(t_dict *envd, char *key);

/*
** parser_line.c
*/

t_job				*parse_line(char *line);

/*
** parsing.c
*/

char				*parsing(char *line, t_dict *envl);

/*
** pipe.c
*/

/*
** read_line.c
*/

int					read_line(int fd, char **line);
void				init_quote(t_quote *q);
int					is_quote_closed(t_quote *q);
void				check_quote(t_quote *q, char *line, int i);
#endif