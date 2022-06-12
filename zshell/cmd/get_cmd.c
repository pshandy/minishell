/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:10:42 by pshandy           #+#    #+#             */
/*   Updated: 2021/10/18 12:10:43 by pshandy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char *args)
{
	char	*limiter;
	char	*buf;
	int		fd;

	limiter = args;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (fd);
	buf = readline("heredoc>> ");
	while (buf != NULL)
	{
		if (ft_strcmp(buf, limiter) == 0)
		{
			free(buf);
			break ;
		}
		ft_putstr_fd(buf, fd);
		ft_putstr_fd("\n", fd);
		free(buf);
		buf = readline("heredoc>> ");
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	return (fd);
}

void	set_file(t_token *token, t_cmd *cmd)
{
	if (token->prev->type == INPUT)
		cmd->infile = open(token->str, O_RDONLY, 0644);
	else if (token->prev->type == HEREDOC)
		cmd->infile = ft_heredoc(token->str);
	else if (token->prev->type == TRUNC)
		cmd->outfile = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token->prev->type == APPEND)
		cmd->outfile = open(token->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->infile == -1)
	{
		cmd->to_skip = 1;
		perror(token->str);
	}
	else if (cmd->infile == -1 || cmd->outfile == -1)
		perror(token->str);
}

void	get_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tmp;

	tmp = data->head->next;
	while (tmp != data->head)
	{
		cmd = cmd_create_elem();
		while (tmp != data->head && tmp->type != PIPE)
		{
			if (tmp->type == CMD)
				cmd->args = add_str(cmd->args, ft_strdup(tmp->str));
			else if (tmp->type == INPUT || tmp->type == HEREDOC
				|| tmp->type == APPEND || tmp->type == TRUNC)
			{
				tmp = tmp->next;
				set_file(tmp, cmd);
			}
			else if (tmp->type == ARG)
				cmd->args = add_str(cmd->args, ft_strdup(tmp->str));
			tmp = tmp->next;
		}
		cmd_lstadd_back(&(data->cmds), cmd);
		if (tmp->type == PIPE)
			tmp = tmp->next;
	}
}
