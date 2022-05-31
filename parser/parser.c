#include "parser.h"

int is_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0
			|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0
			|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int words = 0;

	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str && *str != ' ')
		{
			while (*str && *str != ' ')
				str++;
			words++;
		}
	}
	return (words);
}

char **parse_string(char *str)
{
	int	i;
	char *token;
	char **str_array;

	str_array = malloc(sizeof (char *) * (count_words(str) + 1));
	if (!str_array)
		return (NULL);

	char *olds;
	char *delim = malloc(sizeof(char) * 2);
	*delim = ' ';

	i = 0;
	int flag = 0;
	token = _ft_strtok (str, delim, &olds);
	while (token != NULL)
	{
		if (*olds == '\"' && flag == 0)
		{
			flag = 1;
			*delim = '\"';
		}
		else if (flag == 1)
		{
			flag = 0;
			*delim = ' ';
		}
		str_array[i] = ft_strdup(token);
		token = _ft_strtok (NULL, delim, &olds);
		i++;
	}
	str_array[i] = NULL;

	return (str_array);
}

int validate(char **strarr)
{
	int pipes = 1;

	if (is_operator(*strarr))
	{
		printf("Нельзя начать с оператора!\n");
		return (0);
	}
	while (*strarr)
	{
		if (pipes == 1 && (ft_strcmp(*strarr, "<") == 0 || ft_strcmp(*strarr, "<<") == 0
				|| ft_strcmp(*strarr, ">") == 0 || ft_strcmp(*strarr, ">>") == 0))
		{
			pipes = 0;
		}
		else if (pipes == 0 && ft_strcmp(*strarr, "|") == 0)
		{
			printf("Пайпы должны идти до редиректов!\n");
			return (0);
		}
		if (!is_operator(*strarr) && (ft_strstr(*strarr, "|") != NULL
				|| ft_strstr(*strarr, "<") != NULL || ft_strstr(*strarr, "<<") != NULL
				|| ft_strstr(*strarr, ">") != NULL || ft_strstr(*strarr, ">>") != NULL))
		{
			printf("Операторы должны разделяться пробелом!\n");
			return (0);
		}

		if (is_operator(*strarr) && (*(strarr + 1) == NULL
				|| is_operator(*(strarr + 1))))
		{
			printf("Повторяющиеся операторы или оператор без аргумента!\n");
			return (0);
		}
		*strarr++;
	}
	return (1);
}

typedef struct	s_cmd
{
	char	*command;
	char	**command_args;
	int		cmd_count;
}				t_cmd;


void make_commands()
{

}

int main()
{
	char str[] = "ls -l \"asda asdsd\" asd";

	char **t = parse_string(str);
	validate(t);

	while (*t != NULL)
	{
		printf("Token: %s\n", *t);
		*t++;
	}

//	char str[] = "String   to |parse | | pwd";
//	char *str_array[1024];
//
//	int i = 0;
//	char *token;
//	token = ft_strtok(str, " ");
//	while (token != NULL)
//	{
//		str_array[i] = ft_strdup(token);
//		token = ft_strtok(NULL, " ");
//		i++;
//	}
//
//	for (int i = 0; i < 1024; i++)
//	{
//		if (str_array[i] == NULL)
//			break ;
//		if (is_operator(str_array[i]) && (str_array[i + 1] == NULL || is_operator(str_array[i + 1])))
//		{
//			printf("ERROR!\n");
//			return (0);
//		}
//
//	}
//
//	for (int i = 0; i < 1024; i++)
//	{
//		if (str_array[i] == NULL)
//			break ;
//		printf("%s\n", str_array[i]);
//	}
}
