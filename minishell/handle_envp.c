#include "minishell.h"

static size_t get_length(char **start)
{
	char **end;

	end = start;
	while (*end)
		end++;
	return (end - start);
}

void save_envp(char **envp)
{
	int		length;

	length = get_length(envp);

	g_envp = (char **) malloc(sizeof(char *) * (length + 1));
	if (!g_envp)
		return ;

	g_envp[length] = NULL;
	while (length--)
		g_envp[length] = ft_strdup(envp[length]);

	for (int i = 0; i < get_length(envp); i++)
	{
		printf("%s\n", g_envp[i]);
	}

}
