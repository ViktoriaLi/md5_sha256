/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 18:36:04 by vlikhotk          #+#    #+#             */
/*   Updated: 2017/12/11 18:36:34 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	hash(unsigned char *string, int length, int table_size)
{
	int i;

	i = 0;
	if (length == 2)
		while (length--)
		{
			i = i + (int)string[length] * 17;
		}
	else
		while (length--)
			i = i + ((int)string[length] * length);
	i = i % table_size;
	return (i);
}
