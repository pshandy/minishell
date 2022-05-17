#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

char **g_envp;

void save_envp(char **envp);

/* LIBFT */

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s);

#endif
