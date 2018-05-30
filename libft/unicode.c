/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 17:25:05 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 17:09:24 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	print_unicode2(int bytes_count, wchar_t s, int *count, int len)
{
	int				j;
	int				shift;
	char			res[4];

	j = 0;
	shift = 6;
	while (j < bytes_count)
	{
		res[j] = s >> shift;
		if (j == 0)
			res[j] = (res[j] & 31) + 192;
		else
			res[j] = (res[j] & 63) + 128;
		shift -= 6;
		j++;
	}
	if (((*count) + bytes_count) <= len)
	{
		write(1, res, bytes_count);
		(*count) += bytes_count;
	}
}

void	print_unicode3(int bytes_count, wchar_t s, int *count, int len)
{
	int				j;
	int				shift;
	char			res[4];

	j = 0;
	shift = 12;
	while (j < bytes_count)
	{
		res[j] = s >> shift;
		if (j == 0)
			res[j] = (res[j] & 15) + 224;
		else
			res[j] = (res[j] & 63) + 128;
		shift -= 6;
		j++;
	}
	if (((*count) + bytes_count) <= len)
	{
		write(1, res, bytes_count);
		(*count) += bytes_count;
	}
}

void	print_unicode4(int bytes_count, wchar_t s, int *count, int len)
{
	int				j;
	int				shift;
	char			res[4];

	j = 0;
	shift = 18;
	while (j < bytes_count)
	{
		res[j] = s >> shift;
		if (j == 0)
			res[j] = (res[j] & 7) + 240;
		else
			res[j] = (res[j] & 63) + 128;
		shift -= 6;
		j++;
	}
	if (((*count) + bytes_count) <= len)
	{
		write(1, res, bytes_count);
		*count += bytes_count;
	}
}

void	print_unicode(wchar_t *test, int len, t_argc *params)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (test[i] && i < len)
	{
		if (test[i] <= 127 && (count++ + 1) <= len)
			write(1, &test[i], 1);
		else if (test[i] > 127 && test[i] <= 2047)
			print_unicode2(2, test[i], &count, len);
		else if (test[i] > 2047 && test[i] <= 65535)
			print_unicode3(3, test[i], &count, len);
		else if (test[i] > 65535 && test[i] <= 1114111)
			print_unicode3(4, test[i], &count, len);
		i++;
	}
	if ((*params).specifier != 'C' && (*params).specifier != 'c')
		(*params).res -= count - len;
}

size_t	ft_strlen_wide(wchar_t *s)
{
	size_t i;
	size_t res;

	i = 0;
	res = 0;
	while (s[i] != 0)
	{
		if (s[i] <= 127)
			res++;
		else if (s[i] > 127 && s[i] <= 2047)
			res += 2;
		else if (s[i] > 2047 && s[i] <= 65535)
			res += 3;
		else if (s[i] > 65535 && s[i] <= 1114111)
			res += 4;
		i++;
	}
	return (res);
}
