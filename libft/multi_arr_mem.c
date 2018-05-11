/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_arr_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:38:01 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/12/11 17:44:57 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	***multi_arr_mem(int n, int r, int w)
{
	int		i;
	int		j;
	char	***multi_arr;
	char	*data;
	char	**ptr;

	i = 0;
	j = 0;
	multi_arr = (char ***)malloc(sizeof(char **) * n +
		sizeof(char *) * n * r + n * r * w);
	ptr = (char **)(multi_arr + n);
	data = (char *)(multi_arr + n + n * r);
	while (i < n)
	{
		multi_arr[i] = ptr + i * r;
		j = 0;
		while (j < r)
		{
			multi_arr[i][j] = data + i * r * w + j * w;
			multi_arr[i][j][w - 1] = 0;
			j++;
		}
		i++;
	}
	return (multi_arr);
}
