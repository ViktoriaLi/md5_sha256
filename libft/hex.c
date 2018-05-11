/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:53:20 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 14:16:47 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex(char **res, uintmax_t nbr, t_argc params, unsigned int base)
{
	int			i;
	int			len;
	uintmax_t	d;

	d = nbr;
	len = 1;
	i = 0;
	while (d > base - 1)
	{
		d = d / base;
		len++;
	}
	if (!((*res) = (char *)malloc((len + 1))))
		return ;
	(*res)[len--] = 0;
	while (len >= 0)
	{
		if ((nbr % base) < 10)
			(*res)[len--] = (nbr % base) + 48;
		else if (params.specifier == 'x' || params.specifier == 'p')
			(*res)[len--] = (nbr % base) - 10 + 97;
		else if (params.specifier == 'X')
			(*res)[len--] = (nbr % base) - 10 + 65;
		nbr = nbr / base;
	}
}

void	print_hex_right_align(t_argc *params, t_forprint *elems, intmax_t d)
{
	if ((*elems).spaces > 0)
		while ((*elems).spaces--)
			write(1, " ", 1);
	if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0)
	|| (*params).specifier == 'p')
	{
		(*params).res += 2;
		write(1, "0", 1);
		if ((*params).specifier == 'x' || (*params).specifier == 'p')
			write(1, "x", 1);
		else
			write(1, "X", 1);
	}
	if ((*elems).zeros > 0)
		while ((*elems).zeros--)
			write(1, "0", 1);
	if (d != 0)
		write(1, (*elems).s, (*elems).len);
	else if ((*params).precision != 0)
		write(1, "0", 1);
}

void	print_hex_left_align(t_argc *params, t_forprint *elems, intmax_t d)
{
	if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0)
	|| (*params).specifier == 'p')
	{
		(*params).res += 2;
		write(1, "0", 1);
		if ((*params).specifier == 'x' || (*params).specifier == 'p')
			write(1, "x", 1);
		else
			write(1, "X", 1);
	}
	if ((*elems).zeros > 0)
		while ((*elems).zeros--)
			write(1, "0", 1);
	if (d != 0)
		write(1, (*elems).s, (*elems).len);
	else if ((*params).precision != 0)
		write(1, "0", 1);
	if ((*elems).spaces > 0)
		while ((*elems).spaces--)
			write(1, " ", 1);
}

void	x_elems_count(t_argc *params, t_forprint *elems, intmax_t d)
{
	if ((*params).precision > -1)
		(*elems).zeros = (*params).precision - (*elems).len;
	else if (if_flag((*params).flag, '0', FLAG_LIMIT) &&
	!if_flag((*params).flag, '-', FLAG_LIMIT))
		(*elems).zeros = (*params).width - (*elems).len;
	if ((*elems).zeros > 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len - (*elems).zeros;
	if ((*elems).zeros <= 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len;
	if ((if_flag((*params).flag, '#', FLAG_LIMIT) && d != 0)
	|| (*params).specifier == 'p')
	{
		(*elems).spaces -= 2;
		if (if_flag((*params).flag, '0', FLAG_LIMIT) && ((*params).precision < 0
		|| (*params).specifier == 'p'))
			(*elems).zeros -= 2;
	}
	if ((*elems).zeros > 0)
		(*params).res += (*elems).zeros;
	if ((*elems).spaces > 0)
		(*params).res += (*elems).spaces;
}

void	x_analizator(t_argc *params, va_list ap)
{
	intmax_t	d;
	t_forprint	elems;

	elems_init(&elems);
	elems.len = 0;
	check_stars(params, ap);
	d = va_arg(ap, intmax_t);
	ox_depend_length(&d, (*params).length, params);
	print_hex(&elems.s, d, *params, 16);
	if (d != 0)
		elems.len = ft_strlen(elems.s);
	if (d == 0 && (*params).precision != 0)
		elems.len = 1;
	(*params).res += elems.len;
	x_elems_count(params, &elems, d);
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
		print_hex_left_align(params, &elems, d);
	else
		print_hex_right_align(params, &elems, d);
	print_left(params);
	ft_strdel(&elems.s);
}
