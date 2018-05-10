/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:47:04 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/09 16:48:11 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	init_sha256_vectors(t_addition *iters)
{
	(*iters).a0 = 0x6A09E667;
	(*iters).b0 = 0xBB67AE85;
	(*iters).c0 = 0x3C6EF372;
	(*iters).d0 = 0xA54FF53A;
	(*iters).e0 = 0x510E527F;
	(*iters).f0 = 0x9B05688C;
	(*iters).g0 = 0x1F83D9AB;
	(*iters).h0 = 0x5BE0CD19;
	(*iters).a1 = 0;
	(*iters).b1 = 0;
	(*iters).c1 = 0;
	(*iters).d1 = 0;
	(*iters).e1 = 0;
	(*iters).f1 = 0;
	(*iters).g1 = 0;
	(*iters).h1 = 0;
}

void	init_sha512_vectors(t_addition *iters)
{
	(*iters).aa0 = 0x6a09e667f3bcc908;
	(*iters).bb0 = 0xbb67ae8584caa73b;
	(*iters).cc0 = 0x3c6ef372fe94f82b;
	(*iters).dd0 = 0xa54ff53a5f1d36f1;
	(*iters).ee0 = 0x510e527fade682d1;
	(*iters).ff0 = 0x9b05688c2b3e6c1f;
	(*iters).gg0 = 0x1f83d9abfb41bd6b;
	(*iters).hh0 = 0x5be0cd19137e2179;
	(*iters).aa1 = 0;
	(*iters).bb1 = 0;
	(*iters).cc1 = 0;
	(*iters).dd1 = 0;
	(*iters).ee1 = 0;
	(*iters).ff1 = 0;
	(*iters).gg1 = 0;
	(*iters).hh1 = 0;
}

void	init_md5_vectors(t_addition *iters)
{
	(*iters).a0 = 0x67452301;
	(*iters).b0 = 0xEFCDAB89;
	(*iters).c0 = 0x98BADCFE;
	(*iters).d0 = 0x10325476;
	(*iters).a1 = 0;
	(*iters).b1 = 0;
	(*iters).c1 = 0;
	(*iters).d1 = 0;
}

void	clear_iterators(t_addition *iters)
{
	(*iters).i = 0;
	(*iters).j = 0;
	(*iters).k = 0;
	(*iters).m = 0;
}

void	clear_struct(t_args *params, int argc)
{
	(*params).bytes_read = 0;
	(*params).ifd = 0;
	(*params).if_no_file = 0;
	(*params).cipher = NULL;
	(*params).md5_str = NULL;
	(*params).filename = NULL;
	(*params).argvs = NULL;
}
