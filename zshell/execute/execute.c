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

int	g_fork;

void	launch_child(t_data *data, t_cmd *cmd)
{
	char	*tmp;
	char	**tmpenv;

	if (cmd->to_skip == 1)
		exit(1);
	tmp = NULL;
	if (is_built_in(cmd->args[0]))
		launch_builtin(data, cmd);
	else
	{
		tmp = is_cmd_present(data, cmd);
		if (tmp == NULL)
		{
			if (!ft_strlen(cmd->args[0]) == 0)
				perror(cmd->args[0]);
			data->exit_code = 127;
		}
		else
		{
			tmpenv = hashmap_to_array(data);
			execve(tmp, cmd->args, tmpenv);
		}
	}
	exit (data->exit_code);
}

void	preset_fork(t_data *data, t_cmd *cmd, int *fdin, int *fdout)
{
	int	fd[2];

	dup2(*fdin, 0);
	close(*fdin);
	if (cmd->next != data->cmds)
	{
		pipe(fd);
		if (cmd->outfile >= 0)
			*fdout = cmd->outfile;
		else
			*fdout = fd[1];
		if (cmd->next->infile >= 0)
			*fdin = cmd->next->infile;
		else
			*fdin = fd[0];
	}
	dup2(*fdout, 1);
	close(*fdout);
}

void	execute2(t_data *data, t_cmd *cmd, int tmpin, int tmpout)
{
	int	fdin;
	int	fdout;

	if (cmd->infile >= 0)
		fdin = cmd->infile;
	else
		fdin = dup(tmpin);
	while (cmd != data->cmds)
	{
		if (cmd->next == data->cmds)
		{
			if (cmd->outfile >= 0)
				fdout = cmd->outfile;
			else
				fdout = dup(tmpout);
		}
		preset_fork(data, cmd, &fdin, &fdout);
		g_fork = fork();
		if (g_fork == 0)
			launch_child(data, cmd);
		waitpid(g_fork, &(data->exit_code), 0);
		data->exit_code = data->exit_code / 256;
		cmd = cmd->next;
	}
	close(fdin);
}

void	execute(t_data *data)
{
	int		tmpout;
	int		tmpin;
	t_cmd	*cmd;

	cmd = data->cmds->next;
	if (is_built_in(cmd->args[0]) && cmd->next == data->cmds
		&& cmd->to_skip == 0)
		launch_builtin(data, cmd);
	else
	{
		tmpin = dup(0);
		tmpout = dup(1);
		execute2(data, cmd, tmpin, tmpout);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
	}
}
