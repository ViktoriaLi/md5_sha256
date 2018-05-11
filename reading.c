/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:03:31 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/11 15:51:40 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
	unsigned int	len;
	unsigned int	limit;

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
		print_sha256_result(iters, params, 1);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		print_sha512_result(iters, params, 1);
}

void	md5_reading(int fd, t_args *params, int len, t_addition *iters)
{
	int ind;

	ind = 0;
	clear_iterators(iters);
	while (((*iters).k = read(fd, &params->md5_buf, len)) > 0)
	{
		(*params).bytes_read += (*iters).k;
		if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0 && fd == 0)
			ft_printf("%s", (*params).md5_buf);
		if ((*iters).k < len)
			add_padding_md5(params, len, (*iters).k);
		start_hashing(params, (*iters).k, iters);
	}
	last_block(params, iters);
	if (fd == 0)
		ind = 2;
	if (ft_strcmp((*params).cipher, "md5") == 0)
		print_md5_result(iters, params, ind);
	if (ft_strcmp((*params).cipher, "sha256") == 0)
		print_sha256_result(iters, params, ind);
	if (ft_strcmp((*params).cipher, "sha512") == 0)
		print_sha512_result(iters, params, ind);
}

void	reading_cases(t_args *params, t_addition *iters, int len)
{
	if (((ft_strcmp((*params).cipher, "md5") == 0 ||
	ft_strcmp((*params).cipher, "sha256") == 0 ||
	ft_strcmp((*params).cipher, "sha512") == 0)))
	{
		if (find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
			md5_reading(0, params, len, iters);
		vectors_initiation(params, iters);
		if (find_symb((*params).flags, 's', FLAG_LEN) >= 0)
		{
			(*params).bytes_read = ft_strlen((char *)(*params).md5_str);
			make_short_blocks_md5(params,
			(*params).bytes_read, (*params).md5_str, iters);
		}
		vectors_initiation(params, iters);
		if ((*params).ifd > 1)
			md5_reading((*params).ifd, params, len, iters);
		vectors_initiation(params, iters);
		if ((find_symb((*params).flags, 's', FLAG_LEN) < 0 &&
		(*params).ifd < 1) && find_symb((*params).flags, 'p', FLAG_LEN) < 0)
			md5_reading(0, params, len, iters);
	}
}
