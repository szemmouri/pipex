/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:39:08 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/24 15:21:05 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_file(t_fd *fd_t, int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close_fds(fd_t);
		exit(EXIT_FAILURE);
	}
}

void	free_dstr(char **cmds)
{
	int	i;

	i = 0;
	if (!cmds)
		return ;
	while (cmds[i])
	{
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->path)
			free(cmds->path);
		if (cmds->command)
			free_dstr(cmds->command);
		free(cmds);
		cmds = tmp;
	}
}

void	close_fds(t_fd *fd)
{
	close(fd->in);
	close(fd->out);
	close(fd->fd[0]);
	close(fd->fd[1]);
}

void	put_perror(char *msg, t_fd *fd, t_cmd *cmds)
{
	perror(msg);
	free_cmds(cmds);
	close_fds(fd);
	exit(EXIT_FAILURE);
}
