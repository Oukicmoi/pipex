/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:12:08 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/19 20:31:16 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// pipefds leakent dans les childs
// open leak en cas de fail
// crash quand env ou PATH est NULL
// split leak

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	prev_pipefd[2];
	int	outfile_fd;
	int	infile_fd;
	int	pipefd[2];
	pid_t			pid;

	i = 2;
	if (ac < 5)
		return (0);
	if (!envp)
	{
		return(0);
	}
	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	outfile_fd = open(av[ac-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		close(infile_fd);
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (i < ac - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			close(infile_fd);
			close(outfile_fd);
			dblclose(pipefd);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (i == 2)
			{
				dup2(infile_fd, STDIN_FILENO);
				close(infile_fd);
			}
			else if (i > 2)
			{
				dup2(prev_pipefd[0], STDIN_FILENO);
				dblclose(prev_pipefd);

			}
			if (i < ac - 2)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				dblclose(pipefd);

			}
			else if (i == ac - 2)
			{
				dup2(outfile_fd, STDOUT_FILENO);
				close(outfile_fd);
				dblclose(pipefd);
			}
			ft_exec(av[i], envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (i > 2)
			{
				dblclose(prev_pipefd);
			}
			prev_pipefd[0] = pipefd[0];
			prev_pipefd[1] = pipefd[1];
			close(pipefd[1]);
			if (i < ac - 2)
			{
				if (pipe(pipefd) == -1)
				{
					perror("pipe");]
					exit(EXIT_FAILURE);
				}
			}
			dprintf(2, "pipefd[0] %d || pipefd[1] %d\n || outfile_fd %d || infile_fd %d\n ", pipefd[0], pipefd[1], outfile_fd, infile_fd);
		}
		i++;
	}
	close(infile_fd);
	close(outfile_fd);
	dblclose(pipefd);
	while (wait(NULL) > 0)
		;
	return (0);
}
