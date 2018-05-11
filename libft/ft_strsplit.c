/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:09:33 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/08 13:26:08 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	**oneword(char const *s, char **dest, char c, int i)
{
	int k;
	int j;
	int start;

	j = 0;
	k = 0;
	while (s[i] == c)
		i++;
	start = i;
	while (s[i] != c && s[i] != 0)
		i++;
	if (!(dest[j] = (char *)malloc(sizeof(char) * (i - start + 1))))
		return (NULL);
	while (k < i - start)
	{
		dest[j][k] = s[start + k];
		k++;
	}
	dest[j++][k] = 0;
	return (dest);
}

static char	**free_mem(char **dest, int i, int j, int start)
{
	if (!(dest[j] = (char *)malloc(sizeof(char) * (i - start + 1))))
	{
		j = j - 1;
		while (j >= 0)
		{
			free(dest[j]);
			dest[j] = NULL;
			j--;
		}
		return (NULL);
	}
	return (dest);
}

static char	**mainsplit(char const *s, char **dest, char c, int i)
{
	int k;
	int j;
	int start;

	j = 0;
	while (s[i] != 0)
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != 0)
				i++;
			if (!(free_mem(dest, i, j, start)))
				return (NULL);
			k = 0;
			while (k < i - start)
			{
				dest[j][k] = s[start + k];
				k++;
			}
			dest[j++][k] = 0;
		}
		i++;
	}
	return (dest);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		words;
	char	**dest;

	i = 0;
	words = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			words++;
		i++;
	}
	if (!(dest = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	if (words == 1)
		dest = oneword(s, dest, c, i);
	else
		dest = mainsplit(s, dest, c, i);
	dest[words] = NULL;
	return (dest);
}
