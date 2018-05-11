/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_multi_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:05:35 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/12/11 18:10:04 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	to_multi_arr(char *buf, char ****mult_ar, int strs, int symbs)
{
	int i;
	int j;
	int k;
	int l;

	i = 0;
	l = 0;
	while (buf[l] != 0)
	{
		j = 0;
		while (j < strs)
		{
			k = 0;
			while (k < symbs)
			{
				(*mult_ar)[i][j][k] = buf[l++];
				k++;
			}
			l++;
			j++;
		}
		l++;
		i++;
	}
	return (i);
}
