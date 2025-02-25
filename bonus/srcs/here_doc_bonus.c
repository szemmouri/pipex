/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:19:46 by szemmour          #+#    #+#             */
/*   Updated: 2025/02/25 10:47:57 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc(char *limiter)
{
	char	*line;
	int		fd;

	limiter = ft_strjoin(limiter, "\n");
	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ft_putstr_fd("here_doc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(line)) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	free(limiter);
}
