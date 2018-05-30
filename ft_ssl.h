/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlikhotk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:15:59 by vlikhotk          #+#    #+#             */
/*   Updated: 2018/05/13 14:47:33 by vlikhotk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"

# define FLAG_LEN 15

typedef struct		s_args
{
	unsigned int	bytes_read;
	char			*cipher;
	char			*filename;
	unsigned char	*md5_str;
	unsigned char	md5_buf[128];
	char			flags[FLAG_LEN];
	int				ifd;
	int				if_no_file;
	unsigned int	words[64];
}					t_args;

typedef struct		s_addition
{
	int					i;
	int					j;
	int					k;
	int					m;
	unsigned int		a0;
	unsigned int		b0;
	unsigned int		c0;
	unsigned int		d0;
	unsigned int		e0;
	unsigned int		f0;
	unsigned int		g0;
	unsigned int		h0;
	unsigned int		a1;
	unsigned int		b1;
	unsigned int		c1;
	unsigned int		d1;
	unsigned int		e1;
	unsigned int		f1;
	unsigned int		g1;
	unsigned int		h1;
	unsigned long long	aa0;
	unsigned long long	bb0;
	unsigned long long	cc0;
	unsigned long long	dd0;
	unsigned long long	ee0;
	unsigned long long	ff0;
	unsigned long long	gg0;
	unsigned long long	hh0;
	unsigned long long	aa1;
	unsigned long long	bb1;
	unsigned long long	cc1;
	unsigned long long	dd1;
	unsigned long long	ee1;
	unsigned long long	ff1;
	unsigned long long	gg1;
	unsigned long long	hh1;
}					t_addition;

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
	unsigned long long eps1;
	unsigned long long ma;
	unsigned long long ch;
	unsigned long long t1;
	unsigned long long t2;
	unsigned long long s0;
	unsigned long long s1;
}					t_sha512_vars;

int					ft_strcmp(const char *s1, const char *s2);
int					ft_printf(const char *format, ...);
size_t				ft_strlen(const char *s);
void				clear_iterators(t_addition *iters);
void				make_short_blocks_md5(t_args *params, int ret,
						unsigned char *str,
						t_addition *iters);
int					find_symb(char *str, char flag, int len);
void				flags_normalize(char *all_flags, t_args *params, int len);
char				*check_md5_and_sha256_flags(int argc, char **argv,
						t_args *params, t_addition *iters);
int					if_valid_args(int argc, char **argv, t_args *params,
						t_addition *iters);
void				clear_struct(t_args *params);
void				start_md5(t_args *params, t_addition *iters, int iflast);
void				add_padding_md5(t_args *params, int len, int count);
void				md5_reading(int fd, t_args *params, int len,
						t_addition *iters);
void				init_md5_vectors (t_addition *iters);
void				round1_func(t_args *params, t_addition *iters, int i,
						int iflast);
void				round2_func(t_args *params, t_addition *iters, int i,
						int iflast);
void				round3_func(t_args *params, t_addition *iters, int i,
						int iflast);
void				round4_func(t_args *params, t_addition *iters, int i,
						int iflast);
void				md5_cycle_shift(unsigned int *word, int rounds,
						t_addition *iters);
unsigned long long	cycle_shift(unsigned long long nbr, int count, int len);
void				print_md5_result(t_addition *iters, t_args *params,
						int source);
void				print_sha256_result(t_addition *iters, t_args *params,
						int source);
void				print_sha512_result(t_addition *iters, t_args *params,
						int source);
unsigned long long	made_words_for_sha512(t_args *params, t_addition *iters);
void				init_sha256_vectors (t_addition *iters);
void				start_sha256(t_args *params, t_addition *iters, int iflast);
void				start_sha512(t_args *params, t_addition *iters, int iflast);
void				init_sha512_vectors (t_addition *iters);
void				round1_1_func(t_addition *iters, int i, int tmp);
void				round2_1_func(t_addition *iters, int i, int tmp);
void				round3_1_func(t_addition *iters, int i, int tmp);
void				round4_1_func(t_addition *iters, int i, int tmp);
unsigned int		make_word_md5(t_args *params, int iflast,
						t_addition *iters);
void				reading_cases(t_args *params, t_addition	*iters,
						int len);
void				vectors_initiation(t_args *params, t_addition	*iters);
void				when_file_found(char **argv, t_args *params, int i,
						int argc);
int					save_ssl_flags(char **argv, t_addition *iters,
						t_args *params, char **all_flags);
void				print_with_flags(int source, t_args *params, int place,
						char *cipher);
char				*ft_strnew(size_t size);
#endif
