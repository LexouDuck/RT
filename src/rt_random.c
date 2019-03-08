

#include "rt_random.h"

#include "../rt.h"
#include "debug.h"

inline static t_u32	ft_rand_bit_shuffle(t_u32 n)
{
	return ((n << 12) ^ (n >> 20));
}

t_u32				ft_srand(int mode, t_u32 value)
{
	static t_u32	new_nb = DEFAULT_SEED;

	if (mode == 1)
		new_nb *= rt.sdl.current_frame;
	if (mode == 2)
		new_nb = value;
	return (new_nb);
}

t_u32				ft_rand(void)
{
	t_float		new_nb;

	new_nb = (CEIL_SQRT_MOD * ft_rand_bit_shuffle(new_nb) + OFFSET) & MODULUS;
	ft_srand(2, new_nb);
	return (new_nb);
}

inline t_u32		ft_rand_0_to_pow2n(t_u32 n)
{
	return (ft_rand() & ((0x1 << n) - 1));
}

inline t_u32		ft_rand_0_to_n(t_u32 n)
{
	return (ft_rand() % n);
}

/*
** XOR swap.
*/
inline int		ft_rand_a_to_b(int a, int b)
{
	if (a < b)
		return (ft_rand_0_to_n(b - a) + a);
	else
		return (ft_rand_0_to_n(a - b) + b);
}

inline t_float		ft_frand_0_to_1(void)
{
	return (((t_float)ft_rand()) / MODULUS);
}

/*
** XOR swap.
*/
inline t_float		ft_frand_a_to_b(t_float a, t_float b)
{
	if (a < b)
		return (ft_frand_0_to_1() * (b - a) + a);
	else
		return (ft_frand_0_to_1() * (a - b) + b);
}