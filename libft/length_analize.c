/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:15:35 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 18:24:09 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_length_hhll(int h_count, int l_count, char **dest)
{
	if (h_count % 2 != 0 && (*dest)[0] != 'l' && (*dest)[0] != 'z'
		&& (*dest)[0] != 'j' && (*dest)[0] != 't')
	{
		(*dest)[0] = 'h';
		(*dest)[1] = 0;
	}
	if (l_count % 2 != 0 && (*dest)[0] != 'l' && (*dest)[0] != 'z'
		&& (*dest)[0] != 'j' && (*dest)[0] != 't')
	{
		(*dest)[0] = 'l';
		(*dest)[1] = 0;
	}
}

void	check_length_hlzj(int *j, int len, char *length, char **dest)
{
	int h_count;
	int l_count;

	h_count = 0;
	l_count = 0;
	while (*j < len)
	{
		if (length[*j] == 'z')
			(*dest)[0] = 'z';
		if (length[*j] == 't' && (*dest)[0] != 'z')
			(*dest)[0] = 't';
		if (length[*j] == 'j' && (*dest)[0] != 'z' && (*dest)[0] != 't')
			(*dest)[0] = 'j';
		if (length[*j] == 'h')
			h_count++;
		if (length[*j] == 'l')
			l_count++;
		(*j)++;
	}
	if ((*dest)[0] == 'z' || (*dest)[0] == 't' || (*dest)[0] == 'j')
		(*dest)[1] = 0;
	check_length_hhll(h_count, l_count, dest);
	ft_strdel(&length);
}

char	*normalize_len_str(char *length, int *i, int *j)
{
	int		m;
	char	*tmp;

	m = 0;
	while (length[*j] == 'h' || length[*j] == 'l' || length[*j] == 'j'
		|| length[*j] == 'z' || length[*j] == 'L' || length[*j] == 't'
		|| length[*j] == ' ')
		(*j)++;
	if (!(tmp = (char *)malloc(*j + 1)))
		return (NULL);
	*j = 0;
	while (length[m] == 'h' || length[m] == 'l' || length[m] == 'j'
		|| length[m] == 'z' || length[m] == 'L' || length[m] == 't'
		|| length[m] == ' ')
	{
		if (length[m] != ' ')
		{
			tmp[*j] = length[m];
			(*j)++;
		}
		m++;
		(*i)++;
	}
	tmp[*j] = 0;
	return (tmp);
}

void	check_length(char *length, int *i, char *dest)
{
	int		j;
	char	*tmp;
	int		k;

	j = 0;
	k = 0;
	tmp = normalize_len_str(length, i, &j);
	if ((ft_len_strnstr(tmp, "ll", j)) && dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'l';
		dest[1] = 'l';
	}
	if (ft_len_strnstr(tmp, "hh", j) && dest[0] != 'l' &&
		dest[0] != 'z' && dest[0] != 'j')
	{
		dest[0] = 'h';
		dest[1] = 'h';
	}
	check_length_hlzj(&k, j, tmp, &dest);
}

void	u_depend_length(uintmax_t *d, char *length, t_argc *params)
{
	if ((ft_strcmp(length, "hh") == 0) && (*params).specifier == 'u')
		*d = (unsigned char)*d;
	else if (ft_strcmp(length, "ll") == 0)
		*d = (unsigned long long)*d;
	else if (length[0] == 'h' && length[1] != 'h' && (*params).specifier == 'u')
		*d = (unsigned short)*d;
	else if (length[0] == 'l')
		*d = (unsigned long)*d;
	else if (length[0] == 'z')
		*d = (size_t)*d;
	else if (length[0] == 'j')
		*d = (uintmax_t)*d;
	else if (length[0] == 't')
		*d = (intmax_t)(*d);
	else
	{
		if ((*params).specifier == 'U')
			*d = (unsigned long)*d;
		else
			*d = (unsigned int)*d;
	}
}
