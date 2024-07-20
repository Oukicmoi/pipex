/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:48:17 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/21 01:30:25 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// pipefds leakent dans les childs
// open leak en cas de fail
// crash quand env ou PATH est NULL
// split leak
int     openfd(openfile *inout,int ac,char **av)
{
	inout->infile_fd = open(av[1], O_RDONLY);
	if (inout->infile_fd == -1)
	{
		perror("open");
                return(-1);
	}
	inout->outfile_fd = open(av[ac-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (inout->outfile_fd == -1)
	{
		close(inout->infile_fd);
		perror("open");
                return(-1);
	}
        return(0);
}

int     dup_in(char *argi, int pipefd, pid_t pid,openfile *inout)
{

	pid = fork();
        if (pid == -1)
        {
                perror("fork");
                close(inout->infile_fd);
                close(inout->outfile_fd);
                dblclose(pipefd);
                exit(EXIT_FAILURE);
        }
        if(pid == 0)
        {
                // dup2
        }

}

int	main(int ac, char **av, char **envp)
{
	int	i;
	int	pipefd[2];
	pid_t			pid;
        openfile                inout;

	i = 2;
	if (ac < 5)
		return (0);
	if (!envp)
		return(0);
        if(openfd(&inout,ac,av) == -1)
                exit(EXIT_FAILURE);
        while(i < ac - 2)
        {
                if (pipe(pipefd) == -1)
                {
                        perror("pipe");
                        return(-1);
                }
                close(pipefd[1]);
                if(i == 2)
                {
                        if(dup_in(av[i],inout.infile_fd, pid, &inout) == -1)
                                exit(EXIT_FAILURE);
                }
                else if(dup_in(av[i], pipefd[0], pid, &inout) == -1)
                        exit(EXIT_FAILURE);
        }
        close(inout.infile_fd);
        close(inout.outfile_fd);
}
