# ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <limits.h>

# define F_ALLOC -42

# define INPUT 		1	//"<"
# define HEREDOC 	2	//"<<"
# define TRUNC 		3	//">"
# define APPEND 	4	//">>"
# define PIPE 		5	//"|"
# define CMD 		6	//"|"
# define ARG 		7	//"|"

typedef struct s_hashmap
{
	char				*key;
	char				*value;
	struct s_hashmap	*prev;
	struct s_hashmap	*next;
}		t_hashmap;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				args_num;
	int				infile;
	int				outfile;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_data
{
	int			hashmap_size;
	int			exit_code;
	t_token		*head;
	t_cmd		*cmds;
	t_hashmap	**hashmap;
}		t_data;

t_hashmap	*get_record(t_data *data, char *key);
void	free_hashmap(t_data *data);
int		get_hash(char *str);
int		init_hashmap(t_data *data, int size);
int		add_to_hashmap(t_data *data, char *key, char *value);
int		del_from_hashmap(t_data *data, char *key);
char	*get_value(t_data *data, char *key);
int		_ft_lstadd_back(t_hashmap **hashmap, char *key, char *value);
int		_ft_lstdel(t_hashmap **hashmap, char *key);
int		_ft_lstinit(t_hashmap **hashmap);
void	_ft_lstclear(t_hashmap **lst);
void	print_list(t_hashmap **hashmap);
char	**ft_split2(char *str, char c);

int		handle_envp(t_data *data, char **envp);

/* TOKENIZE */

void	add_char(char **line, char c);
int		check_quotes(char *buf);
char	*handle_dollar(t_data *data, char *str);
int		is_special_char(char *str);
int		quote_pick(char c, int *single_quote, int *double_quote);
int		tokenize(t_data *data, char *line);

int		token_lstadd_back(t_token **token_list, char *str, int type);
int		token_lstinit(t_token **token_list);
void	token_lstclear(t_token **lst);

void	set_type(t_token *token);
char	*get_special_char(char **line);
int		validate(t_data *data);

char	**add_str(char **arr, char *str);
void	get_cmd(t_data *data);
int		cmd_lstinit(t_cmd **cmd_list);
int		cmd_lstadd_back(t_cmd **cmd_list, t_cmd *cmd);
t_cmd	*cmd_create_elem(void);

int		ft_echo(char **args);
int		ft_env(t_data *data);
int		ft_pwd(void);

int		ft_export(t_data *data, char *str);
int		is_letter(char *str);

int		ft_cd(t_data *data, char **args);
int		ft_unset(t_data *data, char *str);

# endif
