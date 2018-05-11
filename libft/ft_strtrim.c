/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:07:27 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/11/08 13:07:30 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char		*main_strtrim(char const *s, int i, int st, char *res)
{
	int	k;

	k = 0;
	while (k < i - st + 1)
	{
		res[k] = (char)s[st + k];
		k++;
	}
	res[k] = 0;
	return (res);
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		st;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	st = i;
	while (s[i] != 0)
		i++;
	while (i > st - 1 && (s[i] == 0 || s[i] == ' ' ||
		s[i] == '\n' || s[i] == '\t'))
		i--;
	if (!(res = (char *)malloc(sizeof(char) * (i - st + 2))))
		return (NULL);
	return (main_strtrim(s, i, st, res));
}
