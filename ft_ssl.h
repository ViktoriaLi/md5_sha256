/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/03/01 18:21:51 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define FLAG_LEN 15

typedef struct		s_args
{
	char	*cipher;
	unsigned char *md5_str;
	unsigned char *md5_buf;
	//int if_full;
	//int desad_count;
  //unsigned char b64_buf[65];
  //unsigned char buf[DES_BLOCK];
  //unsigned char *vector16;
	char flags[FLAG_LEN];
	//int ifd;
	//int ofd;
	//unsigned char *des_key;
	//unsigned char key_res48[6];
	//unsigned char key_res56[7];
	//unsigned char des_output[8];
	//unsigned char des_48_read[65];
	//unsigned char des_48_res[65];
}					t_args;

typedef struct		s_addition
{
  int i;
  int j;
  int k;
  int m;
	unsigned char str1[4];
	unsigned char str2[4];
	unsigned char str3[4];
	unsigned char str4[4];
}					t_addition;

void	*ft_memalloc(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_printf(const char *format, ...);
size_t		ft_strlen(const char *s);

#endif
