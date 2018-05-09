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
	unsigned char md5_buf[128];
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
	unsigned int a0;
	unsigned int b0;
	unsigned int c0;
	unsigned int d0;
	unsigned int e0;
	unsigned int f0;
	unsigned int g0;
	unsigned int h0;
	unsigned int a1;
	unsigned int b1;
	unsigned int c1;
	unsigned int d1;
	unsigned int e1;
	unsigned int f1;
	unsigned int g1;
	unsigned int h1;
	unsigned long long aa0;
	unsigned long long bb0;
	unsigned long long cc0;
	unsigned long long dd0;
	unsigned long long ee0;
	unsigned long long ff0;
	unsigned long long gg0;
	unsigned long long hh0;
	unsigned long long aa1;
	unsigned long long bb1;
	unsigned long long cc1;
	unsigned long long dd1;
	unsigned long long ee1;
	unsigned long long ff1;
	unsigned long long gg1;
	unsigned long long hh1;

}					t_addition;

/*typedef struct		s_sha512
{
  int i;
  int j;
  int k;
  int m;
	unsigned long long a0;
	unsigned long long b0;
	unsigned long long c0;
	unsigned long long d0;
	unsigned long long e0;
	unsigned long long f0;
	unsigned long long g0;
	unsigned long long h0;
	unsigned long long a1;
	unsigned long long b1;
	unsigned long long c1;
	unsigned long long d1;
	unsigned long long e1;
	unsigned long long f1;
	unsigned long long g1;
	unsigned long long h1;
}					t_sha512;*/

typedef struct		s_sha256
{
	unsigned int eps0;
	unsigned int eps1;
	unsigned int ma;
	unsigned int ch;
	unsigned int t1;
	unsigned int t2;
	unsigned int s0;
	unsigned int s1;

}					t_sha256;

typedef struct		s_sha512_vars
{
	unsigned long long eps0;
	unsigned long long  eps1;
	unsigned long long  ma;
	unsigned long long  ch;
	unsigned long long  t1;
	unsigned long long  t2;
	unsigned long long  s0;
	unsigned long long  s1;


}					t_sha512_vars;


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
void start_md5(t_args *params, t_addition *iters, int iflast);
void add_padding_md5(t_args *params, int len, int count);
void	md5_reading(int fd, t_args *params, int len, t_addition *iters);
void init_md5_vectors (t_addition *iters);

void round1_func(t_args *params, t_addition *iters, int i, int iflast);
void round2_func(t_args *params, t_addition *iters, int i, int iflast);
void round3_func(t_args *params, t_addition *iters, int i, int iflast);
void round4_func(t_args *params, t_addition *iters, int i, int iflast);
void md5_cycle_shift(t_addition *iters, int count, int rounds);

void init_sha256_vectors (t_addition *iters);
void start_sha256(t_args *params, t_addition *iters, int iflast);
void start_sha512(t_args *params, t_addition *iters, int iflast);
void init_sha512_vectors (t_addition *iters);

#endif
