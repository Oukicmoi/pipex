/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:50:37 by gtraiman          #+#    #+#             */
/*   Updated: 2023/11/15 16:45:33 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(char const *s, char c)
{
	size_t	word;

	word = 0;
	while (*s)
	{
		if (*s != c)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (word);
}

static char	*get_next_word(char const *s, char c)
{
	char	*word;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (!word)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
	{
		word[len] = s[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

static char	**error(char **result, int i)
{
	while (i >= 0)
		free(result[i--]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		result[i] = get_next_word(s, c);
		if (!result[i])
			return (error(result, i));
		if (result[i])
			s += ft_strlen(result[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
/*
int	main(void)
{
	printf("%p",ft_split("allez les bleus",' '));
	return(0);
}*/