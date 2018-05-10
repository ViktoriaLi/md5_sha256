/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:03:31 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/09 18:11:26 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

void	start_hashing(t_args *params, int count, t_addition *iters)
{
	int len;
	int iflast;

	if (ft_strcmp((*params).cipher, "md5") == 0 ||
		ft_strcmp((*params).cipher, "sha256") == 0)
		len = 55;
	else
		len = 111;
	if (count > len)
		iflast = 1;
	else
		iflast = 0;
	if (ft_strcmp((*params).cipher, "md5") == 0)
		start_md5(params, iters, iflast);
	if (ft_strcmp((*params).cipher, "sha256") == 0)
		start_sha256(params, iters, iflast);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		start_sha512(params, iters, iflast);
}

void	last_block(t_args *params, t_addition *iters)
{
	int	len;
	int	limit;

	if (ft_strcmp((*params).cipher, "md5") == 0 ||
		ft_strcmp((*params).cipher, "sha256") == 0)
		len = 64;
	else
		len = 128;
	if (ft_strcmp((*params).cipher, "md5") == 0 ||
		ft_strcmp((*params).cipher, "sha256") == 0)
		limit = 55;
	else
		limit = 111;
	if ((*params).bytes_read % len == 0 || (*params).bytes_read % len > limit)
	{
		add_padding_md5(params, len, 0);
		if (ft_strcmp((*params).cipher, "md5") == 0)
			start_md5(params, iters, 0);
		if (ft_strcmp((*params).cipher, "sha256") == 0)
			start_sha256(params, iters, 0);
		if (ft_strcmp((*params).cipher, "sha512") == 0)
			start_sha512(params, iters, 0);
	}
}

void	make_short_blocks_md5(t_args *params, int ret, unsigned char *str,
t_addition *iters)
{
	t_addition	count;
	int			len;

	clear_iterators(&count);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		len = 128;
	else
		len = 64;
	while (count.i < ret)
	{
		count.j = 0;
		while (count.i < ret && count.j < len)
			(*params).md5_buf[count.j++] = str[count.i++];
		if (count.j < len)
			add_padding_md5(params, len, count.j);
		start_hashing(params, count.j, iters);
	}
	last_block(params, iters);
	if (ft_strcmp((*params).cipher, "md5") == 0)
		print_md5_result(iters, params, 1);
	if (ft_strcmp((*params).cipher, "sha256") == 0)
		print_sha256_result(iters, params);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		print_sha512_result(iters, params);
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	clear_iterators(iters);
	while (((*iters).k = read(fd, &params->md5_buf, len)) > 0)
	{
		(*params).bytes_read += (*iters).k;
		if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0 && fd == 0)
			printf("%s", (*params).md5_buf);
		if ((*iters).k < len)
			add_padding_md5(params, len, (*iters).k);
		start_hashing(params, (*iters).k, iters);
	}
	last_block(params, iters);
	if (ft_strcmp((*params).cipher, "md5") == 0)
	{
		if (fd != 0)
			print_md5_result(iters, params, 0);
		else
			print_md5_result(iters, params, 2);
	}

	if (ft_strcmp((*params).cipher, "sha256") == 0)
		print_sha256_result(iters, params);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		print_sha512_result(iters, params);
}
