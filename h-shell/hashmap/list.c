#include "../includes/minishell.h"

void	print_list(t_hashmap **hashmap)
{
	t_hashmap *tmp;

	tmp = (*hashmap)->next;
	while (tmp != (*hashmap))
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_lstadd_back(t_hashmap **hashmap, char *key, char *value)
{
	t_hashmap *new;

	new = malloc(sizeof(t_hashmap));
	if (new == NULL)
		return (F_ALLOC);
	new->key = key;
	new->value = value;
	new->prev = (*hashmap)->prev;
	new->next = *hashmap;
	(*hashmap)->prev->next = new;
	(*hashmap)->prev = new;
	return (1);
}

int	ft_lstdel(t_hashmap **hashmap, char *key)
{
	t_hashmap *tmp;

	tmp = (*hashmap)->next;
	while (tmp != (*hashmap))
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_lstinit(t_hashmap **hashmap)
{
	*hashmap = malloc(sizeof(t_hashmap));
	if (hashmap == NULL)
		return (F_ALLOC);

	(*hashmap)->key = NULL;
	(*hashmap)->value = NULL;
	(*hashmap)->prev = *hashmap;
	(*hashmap)->next = *hashmap;
	return (1);
}

void	ft_lstclear(t_hashmap **lst)
{
	t_hashmap	*tmp;
	t_hashmap	*next;

	next = (*lst)->next;
	while (next != *lst)
	{
		tmp = next;
		free(tmp->key);
		free(tmp->value);
		next = next->next;
		free(tmp);
	}
	free(*lst);
}
