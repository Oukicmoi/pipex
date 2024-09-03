/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:41:25 by gtraiman          #+#    #+#             */
/*   Updated: 2024/09/03 14:41:25 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	makeapipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	openfd(t_openfile *inout)
{
	inout->infile_fd = open(inout->argv[1], O_RDONLY);
	if (inout->infile_fd == -1)
	{
		perror("open");
		return (-1);
	}
	inout->outfile_fd = open(inout->argv[inout->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inout->outfile_fd == -1)
	{
		close(inout->infile_fd);
		perror("open");
		return (-1);
	}
	return (0);
}

int	dblclosin(t_openfile *inout)
{
	close(inout->infile_fd);
	close(inout->outfile_fd);
	return (0);
}

int	waitprocess(int *tabpid, t_openfile *inout)
{
	int		i;
	int		status;
	pid_t	result;

	i = 0;
	while (i <= inout->argc - 4)
	{
		result = waitpid(tabpid[i], &status, 0);
		if (result == -1)
		{
			perror("waitpid");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	dblclose(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}
