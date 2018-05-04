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
	int bytes_read;
	char	*cipher;
	char	*filename;
	unsigned char *md5_str;
	unsigned char md5_buf[64];
	unsigned long plaintext_block[16];
	unsigned long md5_length;
	//int if_full;
	//int desad_count;
  //unsigned char b64_buf[65];
  //unsigned char buf[DES_BLOCK];
  //unsigned char *vector16;
	char flags[FLAG_LEN];
	int ifd;
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
	unsigned long a0;
	unsigned long b0;
	unsigned long c0;
	unsigned long d0;
	unsigned long a1;
	unsigned long b1;
	unsigned long c1;
	unsigned long d1;
	/*unsigned char *str1;
	unsigned char *str2;
	unsigned char *str3;
	unsigned char *str4;
	unsigned char *str_a;
	unsigned char *str_b;
	unsigned char *str_c;
	unsigned char *str_d;*/

}					t_addition;

void	*ft_memalloc(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_printf(const char *format, ...);
size_t		ft_strlen(const char *s);
void clear_iterators(t_addition *iters);
void	make_short_blocks_md5(t_args *params, int ret, unsigned char *str, t_addition *iters);
int		find_symb(char *str, char flag, int len);
void flags_normalize(char *all_flags, t_args *params, int len);
int check_md5_and_sha256_flags(int argc, char **argv, t_args *params);
int if_valid_args(int argc, char **argv, t_args *params);
void clear_struct(t_args *params);
void start_md5(t_args *params, t_addition *iters);
void add_padding_md5(t_args *params, int len, int count);
void	md5_reading(int fd, t_args *params, int len, t_addition *iters);
void init_md5_vectors (t_addition *iters);

void round1_func(t_args *params, t_addition *iters, int i);
void round2_func(t_args *params, t_addition *iters, int i);
void round3_func(t_args *params, t_addition *iters, int i);
void round4_func(t_args *params, t_addition *iters, int i);
void md5_cycle_shift(t_addition *iters, int count, int rounds);

#endif
