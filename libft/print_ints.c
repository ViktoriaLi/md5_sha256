/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:46:34 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:51:11 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	print_zeros(t_argc *params, int zeros, char *s)
{
	if (zeros > 0)
	{
		(*params).res += zeros;
		while (zeros--)
			write(1, "0", 1);
	}
	if (((*params).specifier == 'o' || (*params).specifier == 'O') &&
		if_flag((*params).flag, '#', FLAG_LIMIT) &&
		(s[0] != '0' || (*params).precision != -1))
		write(1, "0", 1);
	if (s[0] != '0')
	{
		if ((*params).sign == '-' && s[0] != '-')
			write(1, "-", 1);
		ft_putstr(s);
		if (s[0] == '-')
			(*params).res--;
	}
	else if ((*params).precision != 0)
		write(1, "0", 1);
}

void	print_params_left(char *s, t_argc *params, int zeros, int spaces)
{
	if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
		(*params).specifier != 'o' && (*params).specifier != 'O'
		&& (*params).specifier != 'u' && (*params).specifier != 'U')
	{
		(*params).res += 1;
		spaces -= 1;
		write(1, "+", 1);
	}
	if ((*params).sign == '-' && zeros > 0)
	{
		(*params).sign = 0;
		spaces--;
		write(1, "-", 1);
		if (!if_flag((*params).flag, '-', FLAG_LIMIT))
			zeros += 1;
		else if (if_flag((*params).flag, '-', FLAG_LIMIT))
			spaces++;
	}
	print_zeros(params, zeros, s);
	if (spaces > 0)
	{
		(*params).res += spaces;
		while (spaces--)
			write(1, " ", 1);
	}
}

void	if_space_flag(t_argc *params, int *zeros, int *spaces)
{
	if (if_flag((*params).flag, ' ', FLAG_LIMIT) && (*params).sign != '-'
		&& !if_flag((*params).flag, '+', FLAG_LIMIT)
		&& (*params).specifier != 'u' && (*params).specifier != 'U' &&
		(*params).specifier != 'o' && (*params).specifier != 'O')
	{
		(*params).res += 1;
		write(1, " ", 1);
		*spaces -= 1;
		if ((if_flag((*params).flag, '-', FLAG_LIMIT) ||
			if_flag((*params).flag, '0', FLAG_LIMIT))
			&& (*params).width > 0 && (*params).precision <= 0)
			*zeros -= 1;
	}
}

void	print_spaces(t_argc *params, int *zeros, int *spaces)
{
	if ((*params).sign != '-' && if_flag((*params).flag, '+', FLAG_LIMIT) &&
		(*params).specifier != 'o' && (*params).specifier != 'O')
	{
		(*spaces) -= 1;
		if ((*params).precision <= 0)
			(*zeros) -= 1;
	}
	if ((*spaces) > 0 && (*zeros) > 0)
	{
		if ((*params).sign == '-' && (*zeros) > 0)
			(*spaces)--;
		(*params).res += (*spaces);
		while ((*spaces)--)
			write(1, " ", 1);
	}
	if ((*spaces) > 0 && (*zeros) <= 0)
	{
		if ((*params).sign == '-' && (*zeros) > 0)
			(*spaces)--;
		(*params).res += (*spaces);
		while ((*spaces)--)
			write(1, " ", 1);
	}
}

void	print_params_right(char *s, t_argc *params, int zeros, int spaces)
{
	print_spaces(params, &zeros, &spaces);
	if ((*params).sign == '-' && zeros > 0)
	{
		write(1, "-", 1);
		(*params).sign = 1;
		if ((*params).precision > 0 &&
			!if_flag((*params).flag, '0', FLAG_LIMIT))
			zeros += 1;
	}
	if ((*params).sign != '-' && (*params).sign != 1 &&
		if_flag((*params).flag, '+', FLAG_LIMIT)
		&& (*params).specifier != 'o' && (*params).specifier != 'O'
		&& (*params).specifier != 'u' && (*params).specifier != 'U')
	{
		(*params).res += 1;
		write(1, "+", 1);
	}
	print_zeros(params, zeros, s);
}
