#include <stdio.h>

static float get_random(unsigned int *seed0, unsigned int *seed1)
{

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);  
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x3F800000;  /* bitwise AND, bitwise OR */
	return (res.f);
//	return (res.f - 2.0f) / 2.0f;
}

int main()
{
	int seed0 = 0x1;
	int seed1 = 0x12;
	for (int i = 0; i < 128; ++i)
		printf("%g ", get_random(&seed0, &seed1));
	printf("\n");
	return (0);
}
