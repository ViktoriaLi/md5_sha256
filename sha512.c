#include "ft_ssl.h"
#include <stdio.h>

void add_padding_md5(t_args *params, int len, int count)
{
	if (ft_strcmp((*params).cipher, "md5") == 0 || ft_strcmp((*params).cipher, "sha256") == 0)
	{
		if (count != 0 || (count == 0 && ((*params).bytes_read % 64 == 0)))
		(*params).md5_buf[count++] = 128;
   while (count < len)
     (*params).md5_buf[count++] = 0;
		 if (count < len - 8)
		 {
			 if (((*params).bytes_read * 8) <= 255)
		    	(*params).md5_buf[63] = (*params).bytes_read * 8;
		  	else
		  			(*params).md5_buf[63] = 0;
		 }
	}
	if (ft_strcmp((*params).cipher, "sha512") == 0)
	{
		if (count != 0 ||  (count == 0 && ((*params).bytes_read % 128 == 0)))
		(*params).md5_buf[count++] = 128;
   while (count < len)
     (*params).md5_buf[count++] = 0;
		 if (count < len - 16)
		 {
			 if (((*params).bytes_read * 8) <= 255)
		    	(*params).md5_buf[127] = (*params).bytes_read * 8;
		  	else
		  			(*params).md5_buf[127] = 0;
		 }
	}
  /*count = 0;
  while (count < len)
    printf("%d\n", (*params).md5_buf[count++]);*/
}

void start_sha512(t_args *params, t_addition *iters, int iflast)
{
	t_addition				count;
	t_sha512_vars				add_vars;
	unsigned int tmp1;
	unsigned int tmp2;
	const unsigned long long square[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
		0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

   unsigned long long words[80];
		clear_iterators(&count);

	while (count.i < 16)
	{
		if ((*params).md5_buf[127] == 0 && count.i == 15 && !iflast)
			words[count.i] = (*params).bytes_read * 8;
		else
		{
			tmp1 = (((((*params).md5_buf[count.k++] << 24) & 4294967295) +
				(((*params).md5_buf[count.k++] << 16) & 16777215)
	+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
		tmp2 =
	(((((*params).md5_buf[count.k++] << 24) & 4294967295) +
		(((*params).md5_buf[count.k++] << 16) & 16777215)
	+ (((*params).md5_buf[count.k++] << 8) & 65535) + ((*params).md5_buf[count.k++] & 255)));
			words[count.i] = (((unsigned long)tmp1) << 32) + (tmp2 & 4294967295);
		}
		printf("111%llu\n", words[count.i]);
		count.i++;
	}
	while (count.i < 80)
	{
		add_vars.s0 = cycle_shift(words[count.i-15], 1, 63) ^ cycle_shift(words[count.i-15], 8, 63)	^ (words[count.i-15] >> 7);
add_vars.s1 = cycle_shift(words[count.i-2], 19, 63) ^ cycle_shift(words[count.i-2], 61, 63) ^ (words[count.i-2] >> 6);
		words[count.i] = words[count.i-16] + add_vars.s0 + words[count.i-7] + add_vars.s1;
		count.i++;
	}
	printf("START%llx %llx %llx %llx %llx %llx %llx %llx \n", (*iters).aa0, (*iters).bb0, (*iters).cc0, (*iters).dd0, (*iters).ee0,
	(*iters).ff0, (*iters).gg0, (*iters).hh0);
	(*iters).aa1 = (*iters).aa0;
	(*iters).bb1 = (*iters).bb0;
	(*iters).cc1 = (*iters).cc0;
	(*iters).dd1 = (*iters).dd0;
	(*iters).ee1 = (*iters).ee0;
	(*iters).ff1 = (*iters).ff0;
	(*iters).gg1 = (*iters).gg0;
	(*iters).hh1 = (*iters).hh0;
	count.i = 0;
	while (count.i < 80)
	{
		add_vars.eps0 = cycle_shift((*iters).aa1, 28, 63) ^ cycle_shift((*iters).aa1, 34, 63) ^ cycle_shift((*iters).aa1, 39, 63);
        add_vars.ma = ((*iters).aa1 & (*iters).bb1) ^ ((*iters).aa1 & (*iters).cc1) ^ ((*iters).bb1 & (*iters).cc1);
				  //add_vars.ma = (((*iters).aa1 & (*iters).bb1) | ((*iters).cc1 & ((*iters).aa1 | (*iters).bb1)));
        add_vars.t2 = add_vars.eps0 + add_vars.ma;
        add_vars.eps1 = cycle_shift((*iters).ee1, 14, 63) ^ cycle_shift((*iters).ee1, 18, 63) ^ cycle_shift((*iters).ee1, 41, 63);
        add_vars.ch = ((*iters).ee1 & (*iters).ff1) ^ ((~((*iters).ee1)) & (*iters).gg1);
				//add_vars.ch = ((*iters).gg1 ^ ((*iters).ee1 & ((*iters).ff1 ^ (*iters).gg1)));
        add_vars.t1 = (*iters).hh1 + add_vars.eps1 + add_vars.ch + square[count.i] + words[count.i];
		(*iters).hh1 = (*iters).gg1;
		(*iters).gg1 = (*iters).ff1;
		(*iters).ff1 = (*iters).ee1;
		(*iters).ee1 = (*iters).dd1 + add_vars.t1;
		(*iters).dd1 = (*iters).cc1;
		(*iters).cc1 = (*iters).bb1;
		(*iters).bb1 = (*iters).aa1;
		(*iters).aa1 = add_vars.t1 + add_vars.t2;

		printf("EEE %d %llx %llx %llx %llx %llx %llx %llx %llx \n", count.i, (*iters).aa1, (*iters).bb1, (*iters).cc1, (*iters).dd1, (*iters).ee1,
		(*iters).ff1, (*iters).gg1, (*iters).hh1);
		count.i++;
	}
		(*iters).aa0 += (*iters).aa1;
		(*iters).bb0 += (*iters).bb1;
		(*iters).cc0 += (*iters).cc1;
		(*iters).dd0 += (*iters).dd1;
		(*iters).ee0 += (*iters).ee1;
		(*iters).ff0 += (*iters).ff1;
		(*iters).gg0 += (*iters).gg1;
		(*iters).hh0 += (*iters).hh1;
		//printf("START %lu %lu %lu %lu \n", (*iters).a0, (*iters).b0, (*iters).c0, (*iters).d0);
}
