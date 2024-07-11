/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:01:12 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/09 18:01:17 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	int				x;
	unsigned char	*dest;

	dest = 0;
	x = nmemb * size;
	if (size && x / size != nmemb)
		return (NULL);
	dest = malloc(x);
	if (!dest)
		return (NULL);
	ft_bzero(dest, x);
	return ((void *)dest);
}
/*int main()
{
    size_t nb = 10;
    size_t n = 0; 

    printf("%p\n", ft_calloc(nb, n));
    printf("%p\n", calloc(nb, n));
}*/
