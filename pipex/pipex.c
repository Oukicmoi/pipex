/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:12:08 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/16 17:47:44 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	prev_pipefd[2];
	int	outfile_fd;
	int	infile_fd;
	int	pipefd[2];
	pid_t			pid;

	i = 2;
	if (ac < 3)
		return (0);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	infile_fd = open("file1", O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	outfile_fd = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (i < ac - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (i == 2)
			{
				dup2(infile_fd, STDIN_FILENO);
				close(infile_fd);
			}
			if (i > 2)
			{
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			if (i < ac - 2)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			if (i == ac - 2)
			{
				dup2(outfile_fd, STDOUT_FILENO);
				close(outfile_fd);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			ft_exec(av[i], envp);
		}
		else
		{
			if (i > 2)
			{
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			prev_pipefd[0] = pipefd[0];
			prev_pipefd[1] = pipefd[1];
			if (i < ac - 2)
			{
				if (pipe(pipefd) == -1)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
			}
		}
		i++;
	}
	close(outfile_fd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
