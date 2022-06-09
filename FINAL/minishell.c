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
			execute(data);
			token_lstclear(&(data->head));
			cmd_lstclear(&(data->cmds));
		}

		free(buf);
		buf = readline("minishell >");
	}
}
int g_fork;
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_fork > 0)
			 kill(g_fork,SIGKILL);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_fork == 0)
			rl_redisplay();
	}
}

void	sig_seg(int code)
{
	(void) code;
	write(1, "Segmentation fault\n", 19);
}

void	sig_sbrt(int code)
{
	(void) code;
	write(1, "abort\n", 6);
}

void	init_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, &sig_seg);
	signal(SIGABRT, &sig_sbrt);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (printf("У шелла нет аргументов!\n"));
	if (handle_envp(&data, envp) == F_ALLOC)
		return (-1);
	init_signal();
	promt(&data);
	free_hashmap(&data);
}
