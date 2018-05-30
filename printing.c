/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:25:39 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/11 15:02:32 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	make_little_endian_32(t_addition *iters, unsigned int *x)
{
	x[0] = (((*iters).a0 >> 24) & 255) | (((*iters).a0 << 8) & 16711680) |
		(((*iters).a0 >> 8) & 65280) | (((*iters).a0 << 24) & 4278190080);
	x[1] = (((*iters).b0 >> 24) & 255) | (((*iters).b0 << 8) & 16711680) |
		(((*iters).b0 >> 8) & 65280) | (((*iters).b0 << 24) & 4278190080);
	x[2] = (((*iters).c0 >> 24) & 255) | (((*iters).c0 << 8) & 16711680) |
		(((*iters).c0 >> 8) & 65280) | (((*iters).c0 << 24) & 4278190080);
	x[3] = (((*iters).d0 >> 24) & 255) | (((*iters).d0 << 8) & 16711680) |
		(((*iters).d0 >> 8) & 65280) | (((*iters).d0 << 24) & 4278190080);
	x[4] = (((*iters).e0 >> 24) & 255) | (((*iters).e0 << 8) & 16711680) |
		(((*iters).e0 >> 8) & 65280) | (((*iters).e0 << 24) & 4278190080);
	x[5] = (((*iters).f0 >> 24) & 255) | (((*iters).f0 << 8) & 16711680) |
		(((*iters).f0 >> 8) & 65280) | (((*iters).f0 << 24) & 4278190080);
	x[6] = (((*iters).g0 >> 24) & 255) | (((*iters).g0 << 8) & 16711680) |
		(((*iters).g0 >> 8) & 65280) | (((*iters).g0 << 24) & 4278190080);
	x[7] = (((*iters).h0 >> 24) & 255) | (((*iters).h0 << 8) & 16711680) |
		(((*iters).h0 >> 8) & 65280) | (((*iters).h0 << 24) & 4278190080);
}

void	print_sha256_result(t_addition *iters, t_args *params, int source)
{
	int					i;
	static unsigned int	x[8];
	unsigned char		*y;

	i = 0;
	y = (unsigned char *)x;
	make_little_endian_32(iters, x);
	print_with_flags(source, params, 0, "SHA256");
	while (i < 32)
	{
		if (y[i] < 16)
			ft_printf("0%x", y[i++]);
		else
			ft_printf("%x", y[i++]);
	}
	print_with_flags(source, params, 1, "SHA256");
}

void	make_little_endian_64_1(t_addition *iters)
{
	(*iters).ee0 = ((*iters).ee0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).ee0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).ee0 = ((*iters).ee0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).ee0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).ee0 = ((*iters).ee0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).ee0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).ff0 = ((*iters).ff0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).ff0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).ff0 = ((*iters).ff0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).ff0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).ff0 = ((*iters).ff0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).ff0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).gg0 = ((*iters).gg0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).gg0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).gg0 = ((*iters).gg0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).gg0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).gg0 = ((*iters).gg0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).gg0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).hh0 = ((*iters).hh0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).hh0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).hh0 = ((*iters).hh0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).hh0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).hh0 = ((*iters).hh0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).hh0 & 0xFF00FF00FF00FF00) >> 8;
}

void	make_little_endian_64(t_addition *iters)
{
	(*iters).aa0 = ((*iters).aa0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).aa0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).aa0 = ((*iters).aa0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).aa0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).aa0 = ((*iters).aa0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).aa0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).bb0 = ((*iters).bb0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).bb0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).bb0 = ((*iters).bb0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).bb0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).bb0 = ((*iters).bb0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).bb0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).cc0 = ((*iters).cc0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).cc0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).cc0 = ((*iters).cc0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).cc0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).cc0 = ((*iters).cc0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).cc0 & 0xFF00FF00FF00FF00) >> 8;
	(*iters).dd0 = ((*iters).dd0 & 0x00000000FFFFFFFF) << 32 |
		((*iters).dd0 & 0xFFFFFFFF00000000) >> 32;
	(*iters).dd0 = ((*iters).dd0 & 0x0000FFFF0000FFFF) << 16 |
		((*iters).dd0 & 0xFFFF0000FFFF0000) >> 16;
	(*iters).dd0 = ((*iters).dd0 & 0x00FF00FF00FF00FF) << 8 |
		((*iters).dd0 & 0xFF00FF00FF00FF00) >> 8;
	make_little_endian_64_1(iters);
}

void	print_sha512_result(t_addition *iters, t_args *params, int source)
{
	int					i;
	unsigned long long	x[8];
	unsigned char		*y;

	i = 0;
	y = (unsigned char *)x;
	make_little_endian_64(iters);
	x[0] = (*iters).aa0;
	x[1] = (*iters).bb0;
	x[2] = (*iters).cc0;
	x[3] = (*iters).dd0;
	x[4] = (*iters).ee0;
	x[5] = (*iters).ff0;
	x[6] = (*iters).gg0;
	x[7] = (*iters).hh0;
	print_with_flags(source, params, 0, "SHA512");
	while (i < 64)
	{
		if (y[i] < 16)
			ft_printf("0%x", y[i++]);
		else
			ft_printf("%x", y[i++]);
	}
	print_with_flags(source, params, 1, "SHA512");
}
