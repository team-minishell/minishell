#ifndef MINI_SHELL
# define MINI_SHELL

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# define MALLOC_ERROR	100
# define KEY_LEFT		0x0107
# define KEY_RIGHT		0x0108

/*
** struct
*/

typedef struct		s_redirect
{
	char				*sign;		// > < >>
	int					save_fd;	// fd 원상복구를 위한 저장본
	char				*filepath;	// 목표지점
	struct s_redirect	*next;		// 다음 리디렉션
}					t_redirect;

typedef struct		s_command
{
	char			*cmd;			//명령어
	char			**argv;			//인자
	int				idx;			//모름
}					t_command;

typedef struct		s_job
{
	char			*str;			//세미콜론으로 구분된 하나의 문자열
	t_command		command;
	t_redirect		redirect;
	struct s_job	*next;			//다음 문자열
}					t_job;

typedef struct	s_quote
{
	int		sq;						//작은 따옴표
	int		dq;						//큰 따옴표
}				t_quote;

typedef struct		s_dict
{
	char			*key;			//환경변수의 키 (e.g SHELL)
	char			*value;			//환경변수의 값 (e.g /bin/zsh)
	struct s_dict	*next;			//다음 환경변수
}					t_dict;

typedef struct		s_env
{
	char			**envp;			//main함수에서 받은 환경변수로, 2차원 배열임
	t_dict			*envd;			//main함수에서 받은 2차원 배열 환경변수를 연결리스트로 바꾼 구조체 포인터
}					t_env;

typedef struct		s_main
{
	pid_t			pid;			//minishell의 프로세스 ID
	t_env			env;			//envp와 envd를 넣어둘 구조체 변수
	t_job			*job;			//명령어(커맨드)를 세미콜론으로 구분해 저장할 구조체 변수
	char			*line;			//명령어(커맨드)를 가리키는 포인터
}					t_main;

/*
** global variable
*/

t_env				*g_env;

/*
** builtin/execute_cd.c
*/

int					execute_cd(char **tokens);

/*
** builtin/execute_echo.c
*/

int					execute_echo(char **tokens);

/*
** builtin/execute_env.c
*/

int					execute_env(char **tokens);

/*
** builtin/execute_export.c
*/

int					execute_export(char **tokens);

/*
** builtin/execute_pwd.c
*/

int					execute_pwd(char **tokens);

/*
** builtin/execute_unset.c
*/

int					execute_unset(char **tokens);

/*
** convert_str.c
*/

char				*convert_str(char *base, char *target, char *convert);
/*
** execution.c
*/

void				execute_job(t_job *job);

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