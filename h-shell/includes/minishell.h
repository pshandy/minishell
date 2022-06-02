/*
 * minishell.h
 *
 *  Created on: May 22, 2022
 *      Author: pshandy
 */

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <readline/readline.h>
#include <readline/history.h>

/* -----HASHMAP----- */

#define F_ALLOC -42

/* -----CMD----- */

typedef struct	s_cmd
{
	char	*command;
	char	**command_args;
}				t_cmd;

/* -----CMD----- */


typedef struct s_hashmap
{
	char *key;
	char *value;
	struct s_hashmap *prev;
	struct s_hashmap *next;
} t_hashmap;

typedef struct s_data
{
	int			hashmap_size;
	t_cmd		*current_cmd;
	t_cmd		**cmd_list;
	t_hashmap	**hashmap;
	char **envp;
} t_data;

/* hashmap.c */

void	show_entry(t_data *data);
void	free_hashmap(t_data *data);
int		get_hash(char *str);
int		init_hashmap(t_data *data, int size);
int		add_to_hashmap(t_data *data, char *key, char *value);
int		del_from_hashmap(t_data *data, char *key);
char	*get_value(t_data *data, char *key);

/* list.c */
int		ft_lstadd_back(t_hashmap **hashmap, char *key, char *value);
int		ft_lstdel(t_hashmap **hashmap, char *key);
int		ft_lstinit(t_hashmap **hashmap);
void	ft_lstclear(t_hashmap **lst);
void	print_list(t_hashmap **hashmap);

/* -----HASHMAP----- */

/* -----UTILS----- */

/* utils.c */
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

/* -----UTILS----- */

int	handle_envp(t_data *data, char **envp);

#endif /* MINISHELL_H_ */
