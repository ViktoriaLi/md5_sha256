/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:37:44 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 17:38:22 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		precision_finder(char *argv, int *i, t_argc *params)
{
	int j;

	j = 0;
	if (argv[*i] == '.')
	{
		(*params).precision = 0;
		(*i)++;
		check_star_anywhere(argv[*i], i, &params->precision);
		if (argv[*i] >= '0' && argv[*i] <= '9')
		{
			if ((*params).precision != '*')
				(*params).precision = ft_printf_atoi(&argv[*i]);
			else if ((*params).width != '*')
				(*params).width = ft_printf_atoi(&argv[*i]);
		}
		else if (medium_flags(argv[*i], i, params))
			if (argv[*i] >= '0' && argv[*i] <= '9')
				(*params).width = ft_printf_atoi(&argv[*i]);
		while (((argv[*i] >= '0' && argv[*i] <= '9')))
			(*i)++;
		return (1);
	}
	return (0);
}

int		check_specifier(char type, t_argc *params, int *i)
{
	if (type == 's' || type == 'S' || type == 'p' || type == 'd' || type == 'D'
	|| type == 'i' || type == 'o' || type == 'O' || type == 'u' || type == 'U'
	|| type == 'x' || type == 'X' || type == 'c' || type == 'C' || type == 'n')
	{
		(*params).specifier = type;
		(*i)++;
		return (type);
	}
	else
		return (0);
}

void	specifier_finder(t_argc *params, char *argv, int *i, va_list ap)
{
	int len;
	int j;

	j = 0;
	len = 0;
	if (check_specifier(argv[*i], params, i))
	{
		len = *i;
		while (argv[*i])
			(*i)++;
		j = *i - len;
		params->left = ft_strsub(argv, len, j);
		(*params).left_len = j;
		argument_analize(params, ap);
		(*i)++;
	}
	else if ((!argv[*i] && (*params).specifier == '%') ||
	(*params).length[0] != 0 || (argv[*i] >= 65 && argv[*i] <= 90) ||
	(argv[*i] >= 97 && argv[*i] <= 122))
	{
		if (((argv[*i] >= 65 && argv[*i] <= 90) || (argv[*i] >= 97
		&& argv[*i] <= 122)))
			(*params).specifier = argv[(*i)++];
		c_analizator(params, ap);
	}
}

void	count_spec_symbs(const char *format, int *i, int *spec_symb)
{
	while (format[*i] && format[(*i)] != '%')
	{
		if (format[*i] == '\r' || format[*i] == '\n' || format[*i] == '\v' ||
		format[*i] == '\t' || format[*i] == '"' || format[*i] == '\'' ||
		format[*i] == '\\' || format[*i] == '\0' || format[*i] == '?' ||
		format[*i] == '\a')
			spec_symb++;
		(*i)++;
	}
}

int		if_percent_found(const char *format, t_argc *params, int *i)
{
	int		j;
	int		len;
	int		spec_symb;

	j = 0;
	len = 0;
	spec_symb = 0;
	struct_init(params);
	if (format[++(*i)] == '%')
	{
		write(1, &format[(*i)++], 1);
		(*params).res++;
		return (0);
	}
	j = (*i);
	count_spec_symbs(format, i, &spec_symb);
	j = (*i) - j;
	if (format[*i] == '%' && spec_symb == 0)
		(*params).specifier = '%';
	len = (*i)--;
	(*params).one_arg = ft_strsub(format, ((*i) - j + 1), j);
	(*i) = len;
	return (1);
}
