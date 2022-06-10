/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c										:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:56:51 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 11:56:52 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_fork;

void	promt(t_data *data)
{
	char	*buf;

	buf = readline("minishell >");
	while (buf != NULL)
	{
		add_history(buf);
		if (ft_strlen(buf) != 0 && tokenize(data, buf))
		{
			cmd_lstinit(&(data->cmds));
			get_cmd(data);
			execute(data);
			token_lstclear(&(data->head));
			cmd_lstclear(&(data->cmds));
		}
		free(buf);
		buf = readline("minishell >");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.exit_code = 0;
	if (argc > 1)
		return (printf("У шелла нет аргументов!\n"));
	if (handle_envp(&data, env) == F_ALLOC)
		return (-1);
	init_signal();
	g_fork = -1;
	promt(&data);
	free_hashmap(&data);
}
