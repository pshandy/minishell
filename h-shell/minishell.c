#include "./includes/minishell.h"

t_cmd *add_cmd(char *name, char *argv)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->command = ft_strdup(name);
	cmd->command_args = ft_split(argv, ',');
	return (cmd);
}

int get_cmd_size(t_cmd **cmd_array)
{
	int	length;

	length = 0;
	while (cmd_array[length])
		length++;
	return (length);
}

void echo(t_data *data)
{
	t_cmd *cur = data->current_cmd;

	int i = 0;
	while (cur->command_args[i])
	{
		printf("%s ", cur->command_args[i]);
		i++;
	}
}

void cd(t_data *data)
{

}

void pwd(t_data *data)
{

}

void export(t_data *data)
{

}

void unset(t_data *data)
{

}

void env(t_data *data)
{

}

void my_exit(t_data *data)
{

}

void other_func(t_data *data)
{
	int 	i;
	char	*tmp;
	t_cmd *cur = data->current_cmd;

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
		_cmd = ft_strjoin(mypath[i], cur->command);
		if (access(_cmd, F_OK) == 0)
		{
			printf("->%s\n", _cmd);

			if (execve(_cmd, cur->command_args, data->envp) == -1)
					printf("Error!\n");

			return ;
		}
		free(_cmd);
		i++;
	}
}

void (*get_cmd(t_data *data))(t_data *)
{
	t_cmd *cmd = data->current_cmd;

	if (ft_strcmp(cmd->command, "echo") == 0)
		return (echo);
	else if (ft_strcmp(cmd->command, "cd") == 0)
		return (cd);
	else if (ft_strcmp(cmd->command, "pwd") == 0)
		return (pwd);
	else if (ft_strcmp(cmd->command, "export") == 0)
		return (export);
	else if (ft_strcmp(cmd->command, "unset") == 0)
		return (unset);
	else if (ft_strcmp(cmd->command, "env") == 0)
		return (env);
	else if (ft_strcmp(cmd->command, "my_exit") == 0)
		return (my_exit);
	else
		return (other_func);
}
void execute(t_cmd **cmd_array, char *infile, char *outfile, t_data *data) {

	int numsimplecommands = get_cmd_size(cmd_array);

	int tmpin = dup(0);
	int tmpout = dup(1);

	int fdin;

	if (infile)
		fdin = open(infile, O_RDONLY);
	else
		fdin = dup(tmpin);

	int ret;
	int fdout;

	for (int i = 0; i < numsimplecommands; i++)
	{
		dup2(fdin, 0);
		close(fdin);

		if (i == numsimplecommands - 1)
		{
			if (outfile)
				fdout = open(outfile, O_WRONLY);
			else
				fdout = dup(tmpout);
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);

		data->current_cmd = data->cmd_list[i];

		void (*command) (t_data *data);
		command = get_cmd(data);

		ret = fork();
		if (ret == 0)
		{
			command(data);
			exit(1);
		}

	}

	dup2(tmpin, 0);
	dup2(tmpout, 1);

	close(tmpin);
	close(tmpout);

	waitpid(ret, NULL, 0);
}

void	to_do(t_data *data)
{
	char *infile = NULL;
	char *outfile = NULL;

	int array_size = 10;
	t_cmd **cmd_array = malloc(sizeof(t_cmd *) * array_size);

	//cmd_array[0] = add_cmd("echo", "custom Text -l");
	cmd_array[0] = add_cmd("echo", "custom Text -l");
	cmd_array[1] = add_cmd("wc", "banana,-l");

	data->cmd_list = cmd_array;
	execute(cmd_array, infile, outfile, data);
}



int	main(int argc, char **argv, char **envp)
{
	t_data data;

	handle_envp(&data, envp);

	to_do(&data);

	printf("\nEnded.\n");
}
