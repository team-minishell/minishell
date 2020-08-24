/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 19:19:53 by nahangyeol        #+#    #+#             */
/*   Updated: 2020/08/24 20:27:11 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

# define MALLOC_ERROR	100

# define RIGHT_ARROW	1
# define LEFT_ARROW		2
# define DOUBLE_ARROW	3

/*
** struct
*/

typedef struct		s_redirect
{
	int					sign;
	int					save_fd;
	char				*filepath;
	struct s_redirect	*next;
}					t_redirect;

/*
** cmd: 명령
** line: redirection 분리 전 원본 문자열
** idx: 파이프로 이어진 커맨드의 갯수
*/

typedef struct		s_command
{
	char			*cmd;
	char			*line;
	char			**argv;
	t_redirect		*redirect;
	int				idx;
}					t_command;

/*
** str: 세미콜론으로 구분된 명령 단위
*/

typedef struct		s_job
{
	char			*str;
	t_command		*command;
	struct s_job	*next;
}					t_job;

typedef struct		s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

/*
** envp: main함수에서 받은 환경변수로, 2차원 배열임
** envd: envp를 딕셔너리 연결리스트로 바꾼 구조체 포인터
*/

typedef struct		s_env
{
	char			**envp;
	t_dict			*envd;
}					t_env;

/*
** pid: minishell의 프로세스
** env: 환경변수에 대한 정보를 담는 구조체 변수
** job: 명령들을 저장하기 위한 구조체 변수
** line: 명령어를 담는 포인터
*/

typedef struct		s_main
{
	pid_t			pid;
	t_env			env;
	t_job			*job;
	char			*line;
}					t_main;

/*
** struct for utils
*/

/*
** sq: 작은 따옴표
** dq: 큰 따옴표
*/

typedef struct		s_quote
{
	int				sq;
	int				dq;
	int				esc;
}					t_quote;

typedef struct		s_split
{
	int		i;
	int		start;
	int		len;
	int		split_idx;
}					t_split;

typedef	struct		s_redi
{
	int			i;
	int			new;
	t_redirect	*first;
	char		*str;
}					t_redi;

/*
** global variable
*/

t_env				*g_env;
int					g_status;
int					g_escape;

/*
** builtin/execute_cd.c
*/

int					execute_cd(t_command *command);

/*
** builtin/execute_echo.c
*/

int					execute_echo(t_command *command);

/*
** builtin/execute_env.c
*/

int					execute_env(void);

/*
** builtin/execute_export.c
*/

int					execute_export(t_command *command);

/*
** builtin/execute_pwd.c
*/

int					execute_pwd(t_command *command);

/*
** builtin/execute_unset.c
*/

int					execute_unset(t_command *command);

/*
** builtin/execute_exit.c
*/

void				execute_exit(t_command *command);

/*
** executer/execute_job.c
*/

void				execute_job(t_job *job);
int					check_builtins(t_command *command);

/*
** executer/set_redirect.c
*/

int					set_in_and_out(int in, int out);
int					set_dup(t_redirect *redirect, int fd1, int fd2);
int					set_redirect(t_redirect *redirect);

/*
** executer/spawn_process.c
*/

int					spawn_proc(int i, int o, t_command *command, t_job *job);

/*
** parser/create_job.c
*/

t_job				*create_job(char *line);

/*
** parser/make_argv.c
*/

int					set_argv(t_job *job);
char				*delete_quote(char *str, int del_quote);

/*
** parser/make_commands.c
*/

char				*ft_strtrim_free_s1(char *s1, char *set);
int					set_command_line(t_job *job, char **cmds);
int					make_commands(t_job *job);

/*
** parser/make_redirects.c
*/

char				*parse_path(char *str);
int					make_redirects(t_job *job);

/*
** parser/parse_line.c
*/

char				*escape_line(char *line);
t_job				*parse_line(char *line);

/*
** reader/check_quote.c
*/

void				init_quote(t_quote *q);
int					is_quote_closed(t_quote *q);
void				check_quote(t_quote *q, char *line, int i);

/*
** reader/read_line.c
*/

int					read_line(int fd, char **line);

/*
** utils/convert_str.c
*/

char				*convert_str(char *base, char *target, char *convert);

/*
** utils/manage_list.c
*/

int					dict_size(t_dict *dict);
t_dict				*make_env_to_dict(char **envp);
char				**make_dict_to_envp(t_dict *envd);
t_dict				*find_env(t_dict *envd, char *key);
char				*find_value_in_dict(t_dict *envd, char *key);

/*
** utils/split_except_quote.c
*/

char				**split_except_quote(char *str, char c);

/*
** check_syntax.c
*/

int					check_syntax(char *str);

/*
** free.c
*/

void				free_job(t_job *job);

/*
** handle_signal.c
*/

int					handle_signal(void);

/*
** main.c
*/

int					ft_perror(char *str, int err_num);

#endif
