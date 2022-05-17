#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	save_envp(envp);

	printf("Compiled!");
}
