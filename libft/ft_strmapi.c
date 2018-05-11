/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:06:44 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/08 13:06:47 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s && f)
	{
		s = (char *)s;
		while (s[i] != 0)
			i++;
		if (!(dest = malloc(sizeof(char) * (i + 1))))
			return (NULL);
		i = 0;
		while (s[i] != 0)
		{
			dest[i] = f(i, (char)s[i]);
			i++;
		}
		dest[i] = 0;
		return (dest);
	}
	return (NULL);
}
