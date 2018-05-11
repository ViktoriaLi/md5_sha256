/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 14:23:30 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 16:45:22 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_left(t_argc *params)
{
	if ((*params).left)
	{
		(*params).res += (*params).left_len;
		write(1, (*params).left, (*params).left_len);
	}
}

void	ox_depend_length(intmax_t *d, char *length, t_argc *params)
{
	if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'o' ||
	(*params).specifier == 'x' || (*params).specifier == 'X'))
		*d = (unsigned char)*d;
	else if (ft_strcmp(length, "ll") == 0)
		*d = (unsigned long long)*d;
	else if (length[0] == 'h' && length[1] != 'h' && (*params).specifier != 'O')
		*d = (unsigned short)*d;
	else if (length[0] == 'l')
		*d = (unsigned long)*d;
	else if (length[0] == 'z')
		*d = (size_t)*d;
	else if (length[0] == 'j')
		*d = (uintmax_t)(*d);
	else if (length[0] == 't')
		*d = (intmax_t)*d;
	else
	{
		if ((*params).specifier == 'O')
			*d = (unsigned long)*d;
		else
		{
			if ((*params).specifier != 'p')
				*d = (unsigned int)*d;
		}
	}
}

void	o_elems_count(t_argc *params, t_forprint *elems, intmax_t d)
{
	if ((*params).precision > 0)
		(*elems).zeros = (*params).precision - (*elems).len;
	else if (if_flag((*params).flag, '0', FLAG_LIMIT) &&
	!if_flag((*params).flag, '-', FLAG_LIMIT) &&
	(*params).precision == -1)
		(*elems).zeros = (*params).width - (*elems).len;
	if (((*elems).zeros > 0 && (*params).width > 1))
		(*elems).spaces = (*params).width - (*elems).len - (*elems).zeros;
	if (((*elems).zeros <= 0 && (*params).width > 1))
		(*elems).spaces = (*params).width - (*elems).len;
	if (if_flag((*params).flag, '#', FLAG_LIMIT))
	{
		if ((*params).precision != -1)
			(*elems).zeros--;
		if (d != 0 || (*params).precision != 0)
		{
			if (d != 0 && ((*params).precision <= 0 || (*elems).zeros < 0))
				(*elems).spaces--;
			if (d != 0 || (*params).precision > 0)
				(*params).res += 1;
		}
		else if (d == 0 && (*params).precision <= 0)
			(*params).res += 1;
	}
}

void	o_analizator(t_argc *params, va_list ap)
{
	intmax_t	d;
	t_forprint	elems;

	elems_init(&elems);
	check_stars(params, ap);
	d = va_arg(ap, intmax_t);
	ox_depend_length(&d, (*params).length, params);
	print_hex(&elems.s, d, *params, 8);
	if (d != 0)
		elems.len = ft_strlen(elems.s);
	else if ((*params).precision != 0)
		elems.len = 1;
	else
		elems.len = 0;
	(*params).res += elems.len;
	o_elems_count(params, &elems, d);
	if_space_flag(params, &elems.zeros, &elems.spaces);
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
		print_params_left(elems.s, params, elems.zeros, elems.spaces);
	else
		print_params_right(elems.s, params, elems.zeros, elems.spaces);
	print_left(params);
	ft_strdel(&elems.s);
}
