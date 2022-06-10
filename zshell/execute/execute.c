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

int g_fork;

void	select_and_exec(int save_stdout, t_data *data, t_cmd *cmd)
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

void    free_mypath(char **mypath)
{
	int    it;

	it = -1;
	if (!mypath)
		return ;
	while (mypath[++it])
		free(mypath[it]);
	free(mypath);
}

char    *run_cmd(t_data *data, t_cmd *cmd)
{
	int        i;
	char    *tmp;
	char    **mypath;
	char    *_cmd;

	if (access(cmd->args[0], F_OK) == 0)
		return (cmd->args[0]);
	mypath = ft_split(get_value(data, "PATH"), ':');
	i = -1;
	while (mypath[++i])
	{
		tmp = mypath[i];
		mypath[i] = ft_strjoin(mypath[i], "/");
		free(tmp);
	}
	i = -1;
	while (mypath && mypath[++i])
    {
		_cmd = ft_strjoin(mypath[i], cmd->args[0]);
		if (access(_cmd, F_OK) == 0)
		{
			free_mypath(mypath);
			return (_cmd);
		}
		free(_cmd);
    }
	free_mypath(mypath);
	return (NULL);
}

void	launch_child(t_data *data, t_cmd *cmd)
{
	if (is_built_in(cmd->args[0]))
		launch_builtin(data, cmd);
	else
	{
		char *tmp = run_cmd(data, cmd);
		if (tmp == NULL)
			perror(cmd->args[0]);
		else
			execve(tmp, cmd->args, hashmap_to_array(data));
	}
	exit (data->exit_code);
}

void	preset_fork(t_data *data, t_cmd *cmd, int *fdin, int *fdout, int tmpout)
{
	dup2(*fdin, 0);
	close(*fdin);

	if (cmd->next == data->cmds)
	{
		if (cmd->outfile >= 0)
			*fdout = cmd->outfile;
		else
			*fdout = dup(tmpout);
	}
	else
	{
		int fd[2];
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
		preset_fork(data, cmd, &fdin, &fdout, tmpout);
		g_fork = fork();
		if (g_fork == 0)
			launch_child(data, cmd);
		cmd = cmd->next;
	}
}

void	execute(t_data *data)
{
	int		tmpout;
	int		tmpin;
	t_cmd	*cmd;

	cmd = data->cmds->next;
	if (is_built_in(cmd->args[0]) && cmd->next == data->cmds)
		launch_builtin(data, cmd);
	else
	{
		tmpin  = dup(0);
		tmpout = dup(1);
		execute2(data, cmd, tmpin, tmpout);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		close(tmpin);
		close(tmpout);
	    if (waitpid(g_fork, &(data->exit_code), 0)
	    		== g_fork && WIFEXITED(data->exit_code))
	    	data->exit_code = WEXITSTATUS(data->exit_code);
	}
}
