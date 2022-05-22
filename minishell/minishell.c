#include "minishell.h"

void prompt()
{
	char *buf;

	buf = readline("minishell>");

	while (buf != NULL)
	{
		add_history(buf);


		free(buf);
		buf = readline("minishell>");
	}

}

void argc_check(int argc)
{
	if (argc > 1)
	{
		printf("usage: ./minishell\n");
		exit(0);
	}
}

void	init_history()
{
	if (access(".history", F_OK) == 0)
		read_history(".history");
	else
	{
		open(".history", O_CREAT | O_APPEND | O_WRONLY, 0644);
		read_history(".history");
	}
}

int _main(int argc, char **argv, char **envp)
{
	char *buf;

	argc_check(argc);
	init_history();

	buf = readline("minishell");
	while (buf != NULL)
	{
		add_history(buf);

		write_history(".history");

		free(buf);
		buf = readline("minishell");
	}
}

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	save_envp(envp);

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler); //TO_DO

	prompt();

	printf("Compiled!");
}
