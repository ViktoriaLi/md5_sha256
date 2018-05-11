/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:00:37 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/04 13:01:05 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;
	int res;

	i = 0;
	if (little[i] == 0)
		return (char *)(big);
	while (big[i] != 0)
	{
		res = i;
		j = 0;
		while (big[i + j] == little[j] && little[j] != 0 && big[i + j] != 0)
			j++;
		if (little[j] == 0)
			return (char *)(&big[res]);
		else
			i++;
	}
	return (NULL);
}
