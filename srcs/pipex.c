/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:38:44 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/25 15:59:13 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static t_cmd	*get_cmd(char **argv, int argc)
{
	t_cmd	*cmds;
	char	**command;
	int		i;

	cmds = NULL;
	i = 2;
	while (i < argc - 1)
	{
		command = split_cmd(argv[i]);
		if (!command)
			return (free_cmds(cmds), NULL);
		push_back(&cmds, command);
		i++;
	}
	return (cmds);
}

static void	child_process(t_fd *fd, t_cmd *cmds, char **envp)
{
	if (fd->in == -1)
	{
		close_fds(fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd->in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close_fds(fd);
		exit(EXIT_FAILURE);
	}
	if (cmds->next)
		dup_file(fd, fd->fd[1]);
	else
		dup_file(fd, fd->out);
	if (!cmds->path)
	{
		ft_putstr_fd(cmds->command[0], 2);
		ft_putendl_fd(": Command Not Found!", 2);
		exit(EXIT_FAILURE);
	}
	close_fds(fd);
	execve(cmds->path, cmds->command, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	wait_childern(t_cmd *cmds)
{
	int	status;

	while (cmds)
	{
		if (waitpid(cmds->pid, &status, 0) == -1)
		{
			free_cmds(cmds);
			perror("Waitpid");
			exit(EXIT_FAILURE);
		}
		status = WEXITSTATUS(status);
		if (status == 127)
		{
			free_cmds(cmds);
			exit(status);
		}
		cmds = cmds->next;
	}
}

static void	ft_pipe(t_cmd *cmds, t_fd *fd, char **envp)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		if (pipe(fd->fd) == -1)
			put_perror("pipe", fd, cmds);
		current->pid = fork();
		if (current->pid == -1)
			put_perror("fork", fd, cmds);
		if (current->pid == 0)
			child_process(fd, current, envp);
		else
		{
			close(fd->fd[1]);
			if (fd->in != STDIN_FILENO)
				close(fd->in);
			if (!cmds->next)
				close(fd->fd[0]);
			fd->in = fd->fd[0];
		}
		current = current->next;
	}
	wait_childern(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmds;
	t_fd	fd;

	if (argc != 5)
		return (ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", 2), 1);
	init_vars(&fd, argv[1], argv[argc - 1]);
	cmds = get_cmd(argv, argc);
	if (!cmds)
	{
		ft_putendl_fd("ERROR: command error!", 2);
		close_fds(&fd);
	}
	if (!resolve_cmd_paths(envp, cmds))
	{
		ft_putendl_fd("ERROR: command error!", 2);
		close_fds(&fd);
	}
	ft_pipe(cmds, &fd, envp);
	free_cmds(cmds);
	close_fds(&fd);
	return (0);
}
