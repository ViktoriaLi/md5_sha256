/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_funcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 19:03:16 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 19:03:17 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	n_analizator(t_argc *params, va_list ap)
{
	int			*n_value;
	intmax_t	*i_value;

	n_value = NULL;
	i_value = NULL;
	if ((*params).specifier == 't')
	{
		i_value = va_arg(ap, intmax_t *);
		if (i_value)
			*i_value = (*params).res;
	}
	else
	{
		n_value = va_arg(ap, int *);
		if (n_value)
			*n_value = (*params).res;
	}
}

void	elems_init(t_forprint *elems)
{
	(*elems).len = 1;
	(*elems).lenf = 0;
	(*elems).spaces = 0;
	(*elems).zeros = 0;
	(*elems).s = NULL;
	(*elems).sf = NULL;
	(*elems).us = NULL;
}

void	struct_init(t_argc *params)
{
	int i;

	i = 0;
	(*params).one_arg = NULL;
	while (i < FLAG_LIMIT)
		(*params).flag[i++] = 0;
	(*params).width = 0;
	(*params).star_width = 0;
	(*params).precision = -1;
	(*params).length[0] = 0;
	(*params).length[1] = 0;
	(*params).length[2] = 0;
	(*params).specifier = 0;
	(*params).left = NULL;
	(*params).left_len = 0;
	(*params).reserve = NULL;
	(*params).sign = 0;
}
