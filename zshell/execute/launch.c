/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c											:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:56:51 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 11:56:52 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	launch_child(t_data *data, t_cmd *cmd)
{
	char	*tmp;

	tmp = NULL;
	if (is_built_in(cmd->args[0]))
		launch_builtin(data, cmd);
	else
	{
		tmp = is_cmd_present(data, cmd);
		if (tmp == NULL)
			perror(cmd->args[0]);
		else
			execve(tmp, cmd->args, hashmap_to_array(data));
	}
	exit (data->exit_code);
}

void	launch_builtin(t_data *data, t_cmd *tmp)
{
	int	tmpin;

	tmpin = -42;
	if (tmp->outfile >= 0)
	{
		tmpin = dup(1);
		dup2(tmp->outfile, 1);
	}
	select_and_exec(data, tmp);
	if (tmp->outfile >= 0)
	{
		dup2(tmpin, 1);
		close(tmpin);
	}
}

void	select_and_exec(t_data *data, t_cmd *cmd)
{
	int	i;

	if (ft_strcmp("echo", cmd->args[0]) == 0)
		data->exit_code = ft_echo(&(cmd->args[1]));
	else if (ft_strcmp("pwd", cmd->args[0]) == 0)
		data->exit_code = ft_pwd();
	else if (ft_strcmp("cd", cmd->args[0]) == 0)
		data->exit_code = ft_cd(data, cmd->args);
	else if (ft_strcmp("env", cmd->args[0]) == 0)
		data->exit_code = ft_env(data);
	else if (ft_strcmp("export", cmd->args[0]) == 0)
	{
		i = 0;
		while (cmd->args[++i])
			data->exit_code = ft_export(data, cmd->args[i]);
	}
	else if (ft_strcmp("unset", cmd->args[0]) == 0)
	{
		i = 0;
		while (cmd->args[++i])
			data->exit_code = ft_unset(data, cmd->args[i]);
	}
	else if (ft_strcmp("exit", cmd->args[0]) == 0)
		ft_exit(data, cmd->args);
}
