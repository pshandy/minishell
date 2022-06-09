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

char *run_cmd(t_data *data, t_cmd *cmd)
{
	int 	i;
	char	*tmp;

	if (access(cmd->cmd, F_OK) == 0)
			return (cmd->cmd);

	char **mypath = ft_split(get_value(data, "PATH"), ':');
	i = 0;
	while (mypath[i])
	{
		tmp = mypath[i];
		mypath[i] = ft_strjoin(mypath[i], "/");
		free(tmp);
		i++;
	}

	i = 0;
	char *_cmd;
	while (mypath && mypath[i])
	{
		_cmd = ft_strjoin(mypath[i], cmd->cmd);
		if (access(_cmd, F_OK) == 0)
			return (_cmd);
		free(_cmd);
		i++;
	}
	return (NULL);
}

void	redirect_in_out(t_data *data, t_cmd *cmd, int *fd)
{
	close(fd[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != data->cmds)
		dup2(fd[1], 1);
	close(fd[1]);
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
	if (tmp->outfile >= 0)
	{
		dup2(tmpin, 1);
		close(tmpin);
	}
}

void	print_message()
{
	char message[] = "message\n";
	write(1, message, strlen(message));
}


int g_fork;
void	execute(t_data *data)
{
	t_cmd *cmd;
//	int ret;

	cmd = data->cmds->next;

	if (is_built_in(cmd->cmd) && cmd->next == data->cmds)
	{
		launch_builtin(data, cmd);
		return ;
	}

	int tmpout = dup(1);
	int	tmpin  = dup(0);

	int	fdin;
	int	fdout;
	if (cmd->infile >= 0)
		fdin = cmd->infile;
	else
		fdin = dup(tmpin);

	while (cmd != data->cmds)
	{
		dup2(fdin, 0);
		close(fdin);

		if (cmd->next == data->cmds)
		{
			if (cmd->outfile >= 0)
				fdout = cmd->outfile;
			else
				fdout = dup(tmpout);
		}
		else
		{
			int fd[2];
			pipe(fd);
			if (cmd->outfile >= 0)
				fdout = cmd->outfile;
			else
				fdout = fd[1];
			if (cmd->next->infile >= 0)
				fdin = cmd->next->infile;
			else
				fdin = fd[0];
		}
		dup2(fdout, 1);
		close(fdout);

//		ret = fork();
		g_fork = fork();
		if (g_fork == 0)
		{
			if (is_built_in(cmd->cmd))
				launch_builtin(data, cmd);
			else
			{
				char *tmp = run_cmd(data, cmd);
				if (tmp == NULL)
					printf("%s не найдена!\n", cmd->cmd);
				else
					execve(tmp, cmd->args, hashmap_to_array(data));
			}
			exit(1);
		}
		cmd = cmd->next;
	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);

	waitpid(g_fork, NULL, 0);
}


//void	execute1(t_data *data)
//{
//	t_cmd	*cmd;
//	int		fd[2];
//	int		fk;
//	char	*tmp;
//
//	cmd = data->cmds->next;
//	if (is_built_in(cmd->cmd) && cmd->next == data->cmds)
//		launch_builtin(data, cmd);
//	else
//	{
//		while (cmd != data->cmds)
//		{
//			if (pipe(fd) == -1)
//				return ;
//			fk = fork();
//			if (fk == 0)
//			{
//				tmp = run_cmd(data, cmd);
//				if (is_built_in(cmd->cmd))
//				{
////					close(fd[0]);
//					if (cmd->outfile < 0 && cmd->next != data->cmds)
//						cmd->outfile = fd[1];
//					else
//						close(fd[1]);
//
//					launch_builtin(data, cmd);
//
//					char buf[1025];
//					read (fd[0], buf, 1024);
//					printf("%s<\n", buf);
////					if (read (fd[0], buf, 1024) > 0)
////						printf("%s\n", buf);
////					else
////						printf("T_T\n");
//					exit(-1);
//				}
//				else if (tmp != NULL)
//				{
//					redirect_in_out(data, cmd, fd);
//					execve(tmp, cmd->args, hashmap_to_array(data));
//					data->exit_code = 126;
//				}
//				exit(1);
//			}
//			else
//			{
//				close(fd[1]);
//				if (cmd->infile >= 0)
//					close(cmd->infile);
//				if (cmd->infile == -2)
//					cmd->infile = fd[0];
//				if (cmd->next != data->cmds && cmd->next->infile == -2)
//					cmd->next->infile = fd[0];
//				else
//					close(fd[0]);
//			}
//			waitpid(fk, NULL, 0);
//			cmd = cmd->next;
//		}
//	}
//}
