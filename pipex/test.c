/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:39:37 by gtraiman          #+#    #+#             */
/*   Updated: 2024/07/18 21:43:45 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

// Fonction pour fermer un pipe
void dblclose(int *pipefd)
{
    close(pipefd[0]);
    close(pipefd[1]);
}

int main(int ac, char **av, char **envp)
{
    int i;
    int prev_pipefd[2]; // Pipe précédent
    int pipefd[2];      // Pipe actuel
    int infile_fd;
    int outfile_fd;
    pid_t pid;

    i = 2;
    if (ac < 5)
        return (0);

    if (!envp)
        return (0);

    // Ouvrir le fichier d'entrée
    infile_fd = open(av[1], O_RDONLY);
    if (infile_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Ouvrir le fichier de sortie
    outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd == -1)
    {
        close(infile_fd);
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (i < ac - 1)
    {
        if (i < ac - 2) // Créer un nouveau pipe sauf pour la dernière commande
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            close(infile_fd);
            close(outfile_fd);
            if (i < ac - 2)
            {
                dblclose(pipefd);
            }
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            if (i == 2) // Première commande
            {
                dup2(infile_fd, STDIN_FILENO);
                close(infile_fd);
            }
            else // Commandes intermédiaires
            {
                dup2(prev_pipefd[0], STDIN_FILENO);
                dblclose(prev_pipefd);
            }

            if (i < ac - 2) // Commandes intermédiaires
            {
                dup2(pipefd[1], STDOUT_FILENO);
                dblclose(pipefd);
            }
            else // Dernière commande
            {
                dup2(outfile_fd, STDOUT_FILENO);
                close(outfile_fd);
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

            if (i < ac - 2) // Mise à jour du pipe précédent pour la prochaine commande
            {
                prev_pipefd[0] = pipefd[0];
                prev_pipefd[1] = pipefd[1];
            }
        }

        i++;
    }

    close(infile_fd);
    close(outfile_fd);
    if (i > 2) // Fermer le dernier pipe utilisé
    {
        dblclose(prev_pipefd);
    }

    while (wait(NULL) > 0)
        ;

    return (0);
}

