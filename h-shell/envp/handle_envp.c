#include "../includes/minishell.h"

int	envp_size(char	**envp)
{
	int	length;

	length = 0;
	while (envp[length])
		length++;
	return (length);
}

int	handle_envp(t_data *data, char **envp)
{
	int		i;
	char	**spl_str;

	data->envp = envp;
	init_hashmap(data, envp_size(envp) * 2);
	i = 0;
	while (i < data->hashmap_size)
	{
		spl_str = ft_split(envp[i], '=');
		if (!spl_str)
			return (-1);
		add_to_hashmap(data, spl_str[0], spl_str[1]);
		i++;
	}
	return (1);
}
