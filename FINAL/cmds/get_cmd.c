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

void get_cmd(t_data *data)
{
	t_token *tmp;

	cmd_lstinit(&(data->cmds));
	tmp = data->head->next;
	while (tmp != data->head)
	{
		t_cmd *cmd = cmd_create_elem();
		while (tmp != data->head && tmp->type != PIPE)
		{
			if (tmp->type == CMD)
			{
				cmd->cmd = ft_strdup(tmp->str);
				cmd->args = add_str(cmd->args, ft_strdup(tmp->str));
			}
			else if (tmp->type == INPUT)
			{
				tmp = tmp->next;
				cmd->infile = open(tmp->str, O_RDONLY, 0644);
			}
			else if (tmp->type == HEREDOC) {
				tmp = tmp->next;
//				cmd->infile = here_doc(data, tmp->str);
			}
			else if (tmp->type == APPEND) {
				tmp = tmp->next;
				cmd->outfile = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			}
			else if (tmp->type == TRUNC) {
				tmp = tmp->next;
				cmd->outfile = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			}
			else if (tmp->type == ARG)
				cmd->args = add_str(cmd->args, tmp->str);
			tmp = tmp->next;
		}
		cmd_lstadd_back(&(data->cmds), cmd);
		if (tmp->type == PIPE)
			tmp = tmp->next;
	}
}
