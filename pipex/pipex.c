/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:12:08 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/11 20:01:05 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	pipefd[2];  // Stocke les fd du pipe :
			    //  - pipefd[0] : lecture seule
			    //  - pipefd[1] : écriture seule
	pid_t	pid, pid2;	// Stocke le retour de fork
	char	buf;	// Stocke la lecture de read
        int     i;

        (void)pid2;
        (void)buf;
        i = 2;
	if (ac < 3)
		return(0);
//	Crée un pipe. En cas d'échec on arrête tout
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
        while(i < ac - 1)
        {
        //	Crée un processus fils
                pid = fork();
                if (pid == -1) // Echec, on arrête tout
                {
                        perror("fork");
                        exit(EXIT_FAILURE);
                }
                else if (pid == 0) // Processus fils
                {
                        ft_exec(av[i],envp);
                }
                i++;
        }
           
}
