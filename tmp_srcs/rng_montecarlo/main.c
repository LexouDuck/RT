#include <stdio.h>
#include <math.h>
#include "ft_random.h"
#include "ft_integral.h"
#include "ft_stat.h"

/*
t_u32		ft_rand(void);
t_u32		ft_rand_0_to_pow2n(t_u32 n);
t_u32		ft_rand_0_to_n(t_u32 n);
t_s32		ft_rand_a_to_b(t_s32 a, t_s32 b);
t_float		ft_frand_0_to_1(void);
t_float		ft_frand_a_to_b(t_float a, t_float b);
*/
/*
t_float		test_func(t_vec_3d const v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
*/
/*
t_float		test_func(t_vec_3d const v)
{
	return (v[0] + v[1] + v[2]);
}
*/

t_float		test_func(t_vec_3d const v)
{
	return (v[0] * (v[1] + v[2]));
}

int			main(void)
{
/*	int			iters = 100;
	t_u32		randint;
	t_float		randfloat;
	int			tmpint = 21;

	printf("\n\nft_rand()\n");
	for (int i = 0; i < iters; ++i)
	{
		randint = ft_rand();
		printf("%d ", randint);
	}

	printf("\n\nft_rand_0_to_pow2n(%d)\n", tmpint);
	for (int i = 0; i < iters; ++i)
	{
		randint = ft_rand_0_to_pow2n(tmpint);
		printf("%d ", randint);
	}

	printf("\n\nft_rand_0_to_n(%d)\n", tmpint);
	for (int i = 0; i < iters; ++i)
	{
		randint = ft_rand_0_to_n(tmpint);
		printf("%d ", randint);
	}

	int		tmpa = 500;
	int		tmpb = -500;
	printf("\n\nft_rand_a_to_b(%d, %d)\n", tmpa, tmpb);
	for (int i = 0; i < iters; ++i)
	{
		randint = ft_rand_a_to_b(tmpa, tmpb);
		printf("%d ", randint);
	}


	printf("\n\nft_frand_0_to_1()\n");
	for (int i = 0; i < iters; ++i)
	{
		randfloat = ft_frand_0_to_1();
		printf("%f ", randfloat);
	}

	printf("\n\nft_frand_a_to_b(%d, %d)\n", tmpa, tmpb);
	for (int i = 0; i < iters; ++i)
	{
		randfloat = ft_frand_a_to_b(tmpa, tmpb);
		printf("%f ", randfloat);
	}

	t_float	xi = 0.;
	t_float	xf = 1.;
	t_float	yi = 0.;
	t_float	yf = 1.;
	t_float	zi = 0.;
	t_float	zf = 1.;
	t_coord_box domain = {{xi, yi, zi}, {xf, yf, zf}};
	printf("\n\nMontecarlo integral of test_func over [%f, %f] * [%f, %f] * [%f, %f]:\n\t%f\n",
											xi, xf, yi, yf, zi, zf, mc_integrate(&test_func, domain));
	*/

	t_u32				sample_nb = 20000;
	printf("Stat test of rng, sample size: %d\n", sample_nb);

	t_int_list			i_lst;
	t_u64				intmax = (t_u32)-1;
	t_float				tmp;
	t_float				decile_inc = sample_nb / 10.;

	i_lst = ft_stat_new_ilst(sample_nb);
	for (int i = 0; i < i_lst.len; ++i)
		i_lst.data[i] = ft_rand_a_to_b(-500, 501);//ft_rand();

	printf("Quicksorting...\n");
	i_lst = ft_stat_quicksort_i(i_lst);
	printf("Done !\n");

	printf("\tMedian:   %12f | intmax   :%lu\n", ft_stat_median_i(i_lst), intmax);
	printf("\tAverage:  %12f | intmax/2 :%lu\n", ft_stat_average_i(i_lst), intmax / 2);
	tmp = ft_stat_variance_i(i_lst);
	printf("\tVariance: %12f | StdDev: %12f\n", tmp, sqrt(tmp));

	printf("\tDeciles int:\n\t\t0 : %12d\n\t\t1 : %12d\n\t\t2 : %12d\n\t\t3 : %12d\n\t\t4 : %12d\n\t\t5 : %12d\n\t\t6 : %12d\n\t\t7 : %12d\n\t\t8 : %12d\n\t\t9 : %12d\n\t\t10: %12d\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);

	printf("\tDeciles uint:\n\t\t0 : %12lu\n\t\t1 : %12lu\n\t\t2 : %12lu\n\t\t3 : %12lu\n\t\t4 : %12lu\n\t\t5 : %12lu\n\t\t6 : %12lu\n\t\t7 : %12lu\n\t\t8 : %12lu\n\t\t9 : %12lu\n\t\t10: %12lu\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);

	printf("\tDeciles hex:\n\t\t0 : %#12lx\n\t\t1 : %#12lx\n\t\t2 : %#12lx\n\t\t3 : %#12lx\n\t\t4 : %#12lx\n\t\t5 : %#12lx\n\t\t6 : %#12lx\n\t\t7 : %#12lx\n\t\t8 : %#12lx\n\t\t9 : %#12lx\n\t\t10: %#12lx\n\n",
		i_lst.data[0],
		i_lst.data[(t_u32)decile_inc],
		i_lst.data[(t_u32)(decile_inc * 2)],
		i_lst.data[(t_u32)(decile_inc * 3)],
		i_lst.data[(t_u32)(decile_inc * 4)],
		i_lst.data[(t_u32)(decile_inc * 5)],
		i_lst.data[(t_u32)(decile_inc * 6)],
		i_lst.data[(t_u32)(decile_inc * 7)],
		i_lst.data[(t_u32)(decile_inc * 8)],
		i_lst.data[(t_u32)(decile_inc * 9)],
		i_lst.data[sample_nb - 1]);


	t_prob_mass		pmf;

	pmf = ft_stat_ilst_to_pmf(i_lst);
	
	printf("Probability mass function for the RNG\n");
	for (int i = 0; i < pmf.len; ++i)
		printf("\t%5d: val %12f; prob %.4f\n", i, pmf.value[i], pmf.prob[i]);

	tmp = 0.;
	for (int i = 0; i < pmf.len; ++i)
		tmp += pmf.prob[i];

	printf("Sum of probs: %.12f\n", tmp);


	return (0);
}
