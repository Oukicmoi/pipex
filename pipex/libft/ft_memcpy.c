/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:09:27 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/15 19:40:53 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dest);
}

/*
int	main(void)
{
	int		n;
	char	dest[2] = "ba";
	char	*src;

	src = "Zoubidou";
	n = 4;
	printf ("Copie moi le nombre de char dans ca %s \n",src);
	ft_memcpy (dest, src, n);
	printf ("Voici les %d premier caractere de %s : %s \n", n,src, dest);
	printf ("Copie moi le nombre de char dans ca %s \n",src);
	memcpy (dest, src, n);
	printf ("Voici les %d premier caractere de %s : %s \n", n,src, dest);
}
*/
