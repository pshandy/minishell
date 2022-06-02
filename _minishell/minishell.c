/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:06:35 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/14 12:06:36 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(int error, char *message)
{
	printf("Ошибка при выделении памяти переменных среды.\n");
	return (error);
}

void	fclear(char ***str)
{
	char **tokens = *str;
	int i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(*str);
}

void prompt(t_data *data)
{
	char *buf;
	char **tokens;

	buf = readline("minishell>");

	while (buf != NULL)
	{
		add_history(buf);

		tokens = get_tokens(buf, data);

		if (!validate(tokens))
		{
			fclear(&tokens);
			return ;
		}

		// ПАРСИНГ КОМАНД

		fclear(&tokens);
		free(buf);
		buf = readline("minishell>");
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
		return (printf("У шелла нет аргументов!\n"));
	if (handle_envp(&data, envp) == F_ALLOC)
		return (error(F_ALLOC, "Ошибка при выделении памяти переменных среды.\n"));
	init_signal();
	prompt(&data);

	free_hashmap(&data);
}
