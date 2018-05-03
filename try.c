#include <stdio.h>

void md5_cycle_shift(unsigned long *a0, int count)
{
  int i = 0;
  int j = 0;
	unsigned long long tmp;
  unsigned long
   tmp1;
	int bits[32];
	//printf("111%d\n", (*iters).a0);
	tmp = *a0;

	j = 31;
	while (i < count)
	{
		bits[i] = (1 << j) & tmp;
    printf("%d\n", bits[i]);
		j--;
		i++;
	}
  printf("TTT%llu\n", tmp);
	tmp <<= count;
  tmp1 = tmp % 4294967296;
  printf("TTT%llu\n", tmp);
	i = 0;
	j = count - 1;
	while (j >= 0)
	{
		if (bits[i])
	    tmp1 |= (1 << j);
	  else
	    tmp1 &= ~(1 << j);
		bits[i]++;
		j--;
	}
	*a0 = tmp1;
		//printf("222%d\n", (*iters).a0);
}

int main(void)
{
  /*long test;

  test = (4023233417 & 2562383102) + (!(4023233417) & 271733878);
  printf("%lu\n", test);*/
  /*unsigned long test;
  test = 1138166207;
  printf("%lu\n", test);
  md5_cycle_shift(&test, 7);
  printf("%lu\n", test);*/
  printf("%d\n", ' ');
}
/*01000011110101110000100110111111
0100001 1110101110000100110111111
11101011100001001101111110100001*/
