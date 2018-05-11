/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_and_stars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:28:02 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:30:18 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		medium_flags(char argv, int *i, t_argc *params)
{
	char	tmp;
	int		j;

	tmp = 0;
	j = 0;
	if (argv == '+' || argv == '#' || argv == '0' ||
		argv == '-' || argv == ' ' || argv == '\'')
	{
		tmp = argv;
		if (!if_flag((*params).flag, argv, FLAG_LIMIT))
		{
			while ((*params).flag[j] != 0)
				j++;
			(*params).flag[j] = argv;
		}
		(*i)++;
		return (1);
	}
	return (0);
}

void	save_flags(int *tmp, int **flag, int j)
{
	int k;

	k = 0;
	if (if_flag(tmp, '+', j))
		(*flag)[k++] = '+';
	if (if_flag(tmp, '#', j))
		(*flag)[k++] = '#';
	if (if_flag(tmp, '0', j))
		(*flag)[k++] = '0';
	if (if_flag(tmp, '-', j))
		(*flag)[k++] = '-';
	if (if_flag(tmp, ' ', j))
		(*flag)[k++] = ' ';
	if (if_flag(tmp, '\'', j))
		(*flag)[k++] = '\'';
	if (if_flag(tmp, 'L', j))
		(*flag)[k++] = 'L';
	if (if_flag(tmp, '$', j))
		(*flag)[k++] = '$';
}

void	check_flags(char *str, int *i, int *flag)
{
	int j;
	int k;
	int *tmp;

	j = 0;
	k = 0;
	tmp = NULL;
	while (str[*i] == '+' || str[*i] == '#' || str[*i] == '0' ||
		str[*i] == '-' || str[*i] == ' ' || str[*i] == '\'' ||
		str[*i] == '$' || str[*i] == 'L')
	{
		j++;
		(*i)++;
	}
	if (!(tmp = (int *)malloc(sizeof(int) * (j + 1))))
		return ;
	tmp[j] = 0;
	*i = 0;
	while (k < j)
		tmp[k++] = str[(*i)++];
	save_flags(tmp, &flag, j);
	if (tmp)
		free(tmp);
}

int		if_flag(int *all_flags, int flag, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		if (all_flags[i] == flag)
			return (1);
		i++;
	}
	return (0);
}

void	check_stars(t_argc *params, va_list ap)
{
	int i;

	i = 0;
	if ((*params).star_width == '*')
		(*params).star_width = va_arg(ap, int);
	if ((*params).width == '*')
	{
		(*params).width = va_arg(ap, int);
		if ((*params).width < 0)
		{
			(*params).width = (*params).width * -1;
			if (!if_flag((*params).flag, '-', FLAG_LIMIT))
			{
				while ((*params).flag[i] != 0)
					i++;
				(*params).flag[i] = '-';
			}
		}
	}
	i = 0;
	if ((*params).precision == '*')
		(*params).precision = va_arg(ap, int);
}
