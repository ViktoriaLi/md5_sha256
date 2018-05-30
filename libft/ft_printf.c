/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:26:19 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 17:55:56 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	argument_analize(t_argc *params, va_list ap)
{
	if ((*params).specifier == 's' && (*params).length[0] != 'l')
		s_analizator(params, ap);
	else if ((*params).specifier == 'S' || ((*params).specifier == 's'
		&& (*params).length[0] == 'l'))
		us_analizator(params, ap);
	else if ((*params).specifier == 'd' || (*params).specifier == 'i'
		|| (*params).specifier == 'D')
		d_analizator(params, ap);
	else if ((*params).specifier == 'o' || (*params).specifier == 'O')
		o_analizator(params, ap);
	else if ((*params).specifier == 'u' || (*params).specifier == 'U')
		u_analizator(params, ap);
	else if ((*params).specifier == 'x' || (*params).specifier == 'X'
		|| (*params).specifier == 'p')
		x_analizator(params, ap);
	else if ((*params).specifier == 'c' && (*params).length[0] != 'l')
		c_analizator(params, ap);
	else if ((*params).specifier == 'C' || ((*params).specifier == 'c'
		&& (*params).length[0] == 'l'))
		uc_analizator(params, ap);
	else if ((*params).specifier == 'n')
		n_analizator(params, ap);
}

void	check_star_anywhere(char c, int *i, int *param)
{
	if (c == '*')
	{
		*param = '*';
		(*i)++;
	}
}

void	argument_save(int i, char *argv, t_argc *params, va_list ap)
{
	check_star_anywhere(argv[i], &i, &params->width);
	check_flags(argv, &i, (*params).flag);
	check_star_anywhere(argv[i], &i, &params->width);
	if ((argv[i] >= '0' && argv[i] <= '9'))
	{
		(*params).star_width = (*params).width;
		(*params).width = ft_printf_atoi(&argv[i]);
		while (argv[i] >= '0' && argv[i] <= '9')
			i++;
	}
	medium_flags(argv[i], &i, params);
	check_star_anywhere(argv[i], &i, &params->width);
	while (precision_finder(argv, &i, params))
	{
		;
	}
	medium_flags(argv[i], &i, params);
	check_star_anywhere(argv[i], &i, &params->width);
	check_length(&argv[i], &i, (*params).length);
	check_star_anywhere(argv[i], &i, &params->width);
	specifier_finder(params, argv, &i, ap);
	if (!(*params).left)
		print_add_text(argv, &i, params);
}

void	print_add_text(const char *format, int *i, t_argc *params)
{
	while (format[*i] && format[*i] != '%')
	{
		write(1, &format[(*i)++], 1);
		(*params).res++;
	}
}

int		ft_printf(const char *format, ...)
{
	int			i;
	int			k;
	va_list		ap;
	t_argc		params;

	i = 0;
	k = 0;
	params.res = 0;
	va_start(ap, format);
	print_add_text(format, &i, &params);
	while (format[i])
	{
		if (format[i] == '%' && !if_percent_found(format, &params, &i))
			continue;
		print_add_text(format, &i, &params);
		if (params.one_arg)
		{
			k = 0;
			argument_save(k, params.one_arg, &params, ap);
		}
		ft_strdel(&params.left);
		ft_strdel(&params.one_arg);
	}
	va_end(ap);
	return (params.res);
}
