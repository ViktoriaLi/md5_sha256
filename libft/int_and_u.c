/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_analize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:51:56 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/02/24 17:08:45 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	int_depend_length(intmax_t *d, char *length, t_argc *params)
{
	if ((ft_strcmp(length, "hh") == 0) && ((*params).specifier == 'd'
	|| (*params).specifier == 'i'))
		*d = (signed char)*d;
	else if (ft_strcmp(length, "ll") == 0)
		*d = (long long)*d;
	else if (length[0] == 'h' && length[1] != 'h' && ((*params).specifier
		== 'd' || (*params).specifier == 'i'))
		*d = (short)*d;
	else if (length[0] == 'l')
		*d = (long)*d;
	else if (length[0] == 'z')
		*d = (ssize_t)(*d);
	else if (length[0] != 'j' && length[0] != 't')
	{
		if ((*params).specifier == 'D')
			*d = (long)*d;
		else
			*d = (int)*d;
	}
}

void	int_elems_count(t_argc *params, t_forprint *elems)
{
	(*params).res += (*elems).len;
	if ((*params).precision > 0)
	{
		(*elems).zeros = (*params).precision - (*elems).len;
		if ((if_flag((*params).flag, '0', FLAG_LIMIT) || if_flag((*params).flag,
		'-', FLAG_LIMIT)) && (*params).sign == '-' && (*params).precision > 0)
			(*elems).zeros++;
	}
	if ((((*elems).zeros < 0 && (*params).precision <= 0) || ((*elems).zeros
	== 0 && ((*params).precision < 0 || (*params).precision > (*elems).len)))
	&& if_flag((*params).flag, '0', FLAG_LIMIT)
	&& !if_flag((*params).flag, '-', FLAG_LIMIT))
		(*elems).zeros = (*params).width - (*elems).len;
	if ((*elems).zeros > 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len - (*elems).zeros;
	if ((*elems).zeros <= 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len;
	if_space_flag(params, &elems->zeros, &elems->spaces);
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
		print_params_left((*elems).s, params, (*elems).zeros, (*elems).spaces);
	else
		print_params_right((*elems).s, params, (*elems).zeros, (*elems).spaces);
	print_left(params);
}

void	d_analizator(t_argc *params, va_list ap)
{
	intmax_t	d;
	t_forprint	elems;

	elems_init(&elems);
	check_stars(params, ap);
	d = va_arg(ap, intmax_t);
	int_depend_length(&d, (*params).length, params);
	if (d < 0)
	{
		(*params).sign = '-';
		d = -1 * d;
	}
	elems.s = ft_printf_itoa(d);
	if (d != 0)
	{
		elems.len = ft_strlen(elems.s);
		if ((*params).sign == '-' && elems.s[0] != '-')
			elems.len++;
		if (elems.s[0] == '-')
			(*params).res++;
	}
	else if ((*params).precision == 0)
		elems.len = 0;
	int_elems_count(params, &elems);
	ft_strdel(&elems.s);
}

void	u_elems_count(t_argc *params, t_forprint *elems)
{
	if ((*params).precision > 0)
		(*elems).zeros = (*params).precision - (*elems).len;
	else if (if_flag((*params).flag, '0', FLAG_LIMIT) &&
		!if_flag((*params).flag, '-', FLAG_LIMIT) &&
		(*params).precision == -1)
		(*elems).zeros = (*params).width - (*elems).len;
	if ((*elems).zeros > 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len - (*elems).zeros;
	if ((*elems).zeros <= 0 && (*params).width > 1)
		(*elems).spaces = (*params).width - (*elems).len;
	if_space_flag(params, &elems->zeros, &elems->spaces);
	if (if_flag((*params).flag, '-', FLAG_LIMIT))
		print_params_left((*elems).s, params, (*elems).zeros, (*elems).spaces);
	else
		print_params_right((*elems).s, params, (*elems).zeros, (*elems).spaces);
	print_left(params);
}

void	u_analizator(t_argc *params, va_list ap)
{
	uintmax_t	d;
	t_forprint	elems;

	elems_init(&elems);
	check_stars(params, ap);
	d = va_arg(ap, uintmax_t);
	u_depend_length(&d, (*params).length, params);
	elems.s = ft_uns_itoa(d);
	if (d != 0)
		elems.len = ft_strlen(elems.s);
	else
	{
		if ((*params).precision != 0)
			elems.len = 1;
		else
			elems.len = 0;
	}
	(*params).res += elems.len;
	u_elems_count(params, &elems);
	ft_strdel(&elems.s);
}
