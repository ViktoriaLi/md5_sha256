/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:06:32 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/08 13:06:35 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*dest;

	i = 0;
	if (s && f)
	{
		while (s[i] != 0)
			i++;
		if (!(dest = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		i = 0;
		while (s[i] != 0)
		{
			dest[i] = f((char)s[i]);
			i++;
		}
		dest[i] = 0;
		return (dest);
	}
	return (NULL);
}
