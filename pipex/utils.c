/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:20:27 by gtraiman          #+#    #+#             */
/*   Updated: 2024/09/01 12:20:27 by gtraiman         ###   ########.fr       */
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
