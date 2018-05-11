/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:59:36 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/04 12:59:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int j;
	int len;
	int res;

	j = 0;
	len = 0;
	while (s[len] != 0)
		len++;
	res = -1;
	if (c == 0)
		return (char*)(&s[len]);
	while (j < len)
	{
		if (s[j] == c)
			res = j;
		j++;
	}
	if (res != -1)
		return (char*)(&s[res]);
	return (NULL);
}
