#include "minishell.h"

void	promt(t_data *data)
{
	char *buf;

	buf = readline("minishell >");
	while (buf != NULL)
	{
		add_history(buf);

		if (ft_strlen(buf) != 0 && tokenize(data, buf))
		{
			get_cmd(data);
//			t_cmd *tmp = data->cmds->next;
//			while (tmp != data->cmds) {
//				printf("Command: %s: ", tmp->cmd);
//				int i = 0;
//				if (tmp->args)
//					while (tmp->args[i])
//					{
//						printf("%s ", tmp->args[i]);
//						i++;
//					}
//				printf("\n");
//				tmp = tmp->next;
//			}
			execute(data);
			token_lstclear(&(data->head));
		}

		free(buf);
		buf = readline("minishell >");
	}

//		if ((ft_strlen(str) != 0) && parse(data, str))
//		{
//			data->cmd = init_cmds(data, data->begin);
//			exec(data);
//			free_token_lst(data);
//		}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (printf("У шелла нет аргументов!\n"));
	if (handle_envp(&data, envp) == F_ALLOC)
		return (-1);
	promt(&data);
	free_hashmap(&data);
}
