/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_built_in(char	*cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp("echo", cmd) == 0 || ft_strcmp("env", cmd) == 0 \
	|| ft_strcmp("export", cmd) == 0 || ft_strcmp("pwd", cmd) == 0 \
	|| ft_strcmp("exit", cmd) == 0 || ft_strcmp("cd", cmd) == 0 \
	|| ft_strcmp("unset", cmd) == 0)
		return (1);
	return (0);
}

void	select_and_exec(int save_stdout, t_data *data, t_cmd *cmd)
{
	int	i;

	if (ft_strcmp("echo", cmd->cmd) == 0)
		data->exit_code = ft_echo(&(cmd->args[1]));
	else if (ft_strcmp("pwd", cmd->cmd) == 0)
		data->exit_code = ft_pwd();
	else if (ft_strcmp("cd", cmd->cmd) == 0)
		data->exit_code = ft_cd(data, cmd->args);
	else if (ft_strcmp("env", cmd->cmd) == 0)
		data->exit_code = ft_env(data);
	else if (ft_strcmp("export", cmd->cmd) == 0)
	{
		i = 0;
		while (cmd->args[++i])
			data->exit_code = ft_export(data, cmd->args[i]);
	}
	else if (ft_strcmp("unset", cmd->cmd) == 0)
	{
		i = 0;
		while (cmd->args[++i])
			data->exit_code = ft_unset(data, cmd->args[i]);
	}

//	else if (ft_strcmp("exit", cmd->cmd) == 0)
//	{
//		if (cmd->outfile >= 0)
//		{
//			dup2(save_stdout, 1);
//			close(save_stdout);
//		}
//		ft_exit(data, cmd);
//	}
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
	select_and_exec(tmpin, data, tmp);
	if (tmp->outfile)
	{
		dup2(tmpin, 1);
		close(tmpin);
	}
}

void	execute(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmds->next;
	if (is_built_in(tmp->cmd) && tmp->next == data->cmds)
		launch_builtin(data, tmp);
	else
	{
		while (tmp != data->cmds)
		{

			tmp = tmp->next;
		}
	}
}
