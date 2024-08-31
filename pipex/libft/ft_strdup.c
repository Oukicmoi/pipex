/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:04:51 by gtraiman          #+#    #+#             */
/*   Updated: 2024/08/31 17:20:30 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	dest = (char *)malloc(i + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int	main(void) {

	const char * original = "The original string.";

	// On duplique la chaîne de caractères initiale.
	char * copy = strdup( original );



	// On affiche la chaîne finale
	printf( "%p\n", original);
	printf( "%p\n", copy );
	printf( "%s\n", original);
	printf( "%s\n", copy );

	// Sans oublier de libérer l'espace mémoire au final.
	free( copy );

	return (EXIT_SUCCESS);
}*/
