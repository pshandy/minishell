/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

# define F_ALLOC -42

typedef struct s_cmd
{
	char	*command;
	char	**command_args;
}				t_cmd;

typedef struct s_hashmap
{
	char				*key;
	char				*value;
	struct s_hashmap	*prev;
	struct s_hashmap	*next;
}		t_hashmap;

typedef struct s_data
{
	int			hashmap_size;
	t_cmd		*current_cmd;
	t_cmd		**cmd_list;
	t_hashmap	**hashmap;
	char		**envp;
}		t_data;

void	show_entry(t_data *data);
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

int		handle_envp(t_data *data, char **envp);

char	*_ft_strtok(char *string, const char *delim, char **save_ptr);
char	*ft_strtok(char *s, const char *delim);

void	init_signal(void);

char	**get_tokens(char *str, t_data *data);
char	*ft_replace(char *str, char *old, char *new);

int		validate(char **strarr);
char	*handle_dollar(char *buf, t_data *data);

#endif
