#include "ft_ssl.h"
#include <stdio.h>

void print_md5_result(t_addition *iters, t_args *params, int source)
{
	int i = 0;
	//if (find_symb((*params).flags, 's', FLAG_LEN) >= 0 && find_symb((*params).flags, 'p', FLAG_LEN) >= 0)
		//printf("%s\n", (*params).md5_str);
	if (source == 1 && find_symb((*params).flags, 's', FLAG_LEN) >= 0 && find_symb((*params).flags, 'q', FLAG_LEN) < 0 && find_symb((*params).flags, 'r', FLAG_LEN) < 0)
		printf("MD5 (\"%s\") = ", (*params).md5_str);
	if (source == 0 && (*params).ifd > 0 && find_symb((*params).flags, 'q', FLAG_LEN) < 0 && find_symb((*params).flags, 'r', FLAG_LEN) < 0)
		printf("MD5 (%s) = ", (*params).filename);

	//printf("%lx", (((*iters).a0>>24)&255) | (((*iters).a0<<8)&16711680) | (((*iters).a0>>8)&65280) | (((*iters).a0<<24)&4278190080));
	//printf("%lx", (((*iters).b0>>24)&255) | (((*iters).b0<<8)&16711680) | (((*iters).b0>>8)&65280) | (((*iters).b0<<24)&4278190080));
	//printf("%lx", (((*iters).c0>>24)&255) | (((*iters).c0<<8)&16711680) | (((*iters).c0>>8)&65280) | (((*iters).c0<<24)&4278190080));
	//printf("%lx", (((*iters).d0>>24)&255) | (((*iters).d0<<8)&16711680) | (((*iters).d0>>8)&65280) | (((*iters).d0<<24)&4278190080));
	unsigned int x[4];
	x[0] = (*iters).a0;
	x[1] = (*iters).b0;
	x[2] = (*iters).c0;
	x[3] = (*iters).d0;
	unsigned char *y;
	y = (unsigned char *)x;
	while (i < 16)
	{
		if (y[i] < 16)
			printf("0%x", y[i]);
		else
			printf("%x", y[i]);
		i++;
	}
	if (source == 0 && (*params).ifd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0 && find_symb((*params).flags, 'q', FLAG_LEN) < 0)
		printf(" %s\n", (*params).filename);
	else if (source == 1 && find_symb((*params).flags, 's', FLAG_LEN) >= 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0 && find_symb((*params).flags, 'q', FLAG_LEN) < 0)
		printf(" \"%s\"\n", (*params).md5_str);
	else
		printf("%c", '\n');
}

void print_sha256_result(t_addition *iters, t_args *params)
{
	/*int i = 0;
	unsigned int x[8];
	x[0] = (*iters).a0;
	x[1] = (*iters).b0;
	x[2] = (*iters).c0;
	x[3] = (*iters).d0;
	x[4] = (*iters).e0;
	x[5] = (*iters).f0;
	x[6] = (*iters).g0;
	x[7] = (*iters).h0;
	unsigned char *y;
	y = (unsigned char *)x;
	while (i < 32)
	{
		if (y[i] < 16)
			printf("0%x", y[i]);
		else
			printf("%x", y[i]);
		i++;
	}*/
	/*if ((*params).ifd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0)
		printf(" %s\n", (*params).filename);
	else
		printf("%c", '\n');*/
  printf("%x%x%x%x%x%x%x%x\n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0, (*iters).e0, (*iters).f0,
  (*iters).g0, (*iters).h0);
}

void print_sha512_result(t_addition *iters, t_args *params)
{
	/*int i = 0;
	unsigned long long x[8];
	x[0] = (*iters).aa0;
	x[1] = (*iters).bb0;
	x[2] = (*iters).cc0;
	x[3] = (*iters).dd0;
	x[4] = (*iters).ee0;
	x[5] = (*iters).ff0;
	x[6] = (*iters).gg0;
	x[7] = (*iters).hh0;
	unsigned char *y;
	y = (unsigned char *)x;
	while (i < 64)
	{
		if (y[i] < 16)
			printf("0%x", y[i]);
		else
			printf("%x", y[i]);
		i++;
	}*/
  printf("%llx%llx%llx%llx%llx%llx%llx%llx\n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0, (*iters).ff0,
  (*iters).gg0, (*iters).hh0);
	/*if ((*params).ifd > 0 && find_symb((*params).flags, 'r', FLAG_LEN) >= 0)
		printf(" %s\n", (*params).filename);
	else
		printf("%c", '\n');*/
}
