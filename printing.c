#include "ft_ssl.h"
#include <stdio.h>

void print_md5_result(t_addition *iters, t_args *params)
{
	/*if (find_symb((*params).flags, 's', FLAG_LEN) >= 0 && find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
		ft_printf("%s\n", (*params).md5_str);
	else if (find_symb((*params).flags, 's', FLAG_LEN) >= 0)
			ft_printf("MD5 (\"%s\") ", (*params).md5_str);*/
	//printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
	//printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
	//printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
	//printf("%lx", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));
	unsigned int x[] = {
		(*iters).a0,
		(*iters).b0,
		(*iters).c0,
		(*iters).d0
	};
	unsigned char *y= (unsigned char *)x;
	for(int i=0; i<16; i++) {
		if (y[i] < 16) {
			printf("0%x", y[i]);
		} else {
			printf("%x", y[i]);
		}
	}

	if ((*params).ifd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0)
		printf(" %s\n", (*params).filename);
	else
		printf("%c", '\n');
}

void print_sha256_result(t_addition *iters, t_args *params)
{
  printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
  (*iters).g0, (*iters).h0);
}

void print_sha512_result(t_addition *iters, t_args *params)
{
  printf("%llx %llx %llx %llx %llx %llx %llx %llx\n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0, (*iters).ff0,
  (*iters).gg0, (*iters).hh0);
}
