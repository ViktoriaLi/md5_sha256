/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:06:57 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/08 13:07:00 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!s || start > ft_strlen(s) || !(dest = (char *)malloc(sizeof(char) *
		(len + 1))))
		return (NULL);
	while (i < len && s[start] != 0)
	{
		dest[i] = (char)s[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}
