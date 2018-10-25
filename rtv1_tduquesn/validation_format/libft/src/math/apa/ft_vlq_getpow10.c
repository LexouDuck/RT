/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_getpow10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 02:04:07 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_apa.h"

static t_vlq	get_larger_pow10(void)
{
	static t_u64	pow10_512[28] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	t_vlq			init_p10_512;

	if (!pow10_512[0])
	{
		init_p10_512 = ft_atovlq("1c633415d4c1d238d98cab8a978a0b1f138cb07303a26\
9974845a71d46b099bc817343afac69be5b0e9449775c1366732a93abade4b2908ee0f95f635e85\
a91924c3fc0695e7fc7153329c57aebfa3edac96e14f5dbc51fb2eb21a2f221e25cfea703ed321a\
a1da1bf28f8733b4475b579c88976c194e6574746c40513c31e1ad9b83a8a975d96976f8f9546dc\
77f27267fc6cf801000000000000000000000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000000000000000000000", HXLOW);
		ft_memcpy(pow10_512, init_p10_512, sizeof(t_u64) * 28);
		ft_vlqdel(&init_p10_512);
	}
	return (pow10_512);
}

/*
** Precalculated stuff, source WolframAlpha:
*/

static t_vlq	get_large_pow10(int pow)
{
	static t_u64	pow10_16[1] = {0x002386f26fc10000};
	static t_u64	pow10_32[2] = {0x800009dc5ada82b7, 0x05acef8100000000};
	static t_u64	pow10_64[4] = {0x8000000000c2781f, 0xa4ffe7d36a9e5fb5,
			0xdc71dac97ed43e02, 0x0000000000000000};
	static t_u64	pow10_128[7] = {0x800093ba47c980e9, 0xc66fe33799b61b58,
			0xc04dc08d3cff5ec2, 0x9ba7217878a9c7e8, 0x8f7e6424ba54f804,
			0x8000000000000000, 0x0000000000000000};
	static t_u64	pow10_256[14] = {0x80000000aa7eebfb, 0xcefcef46eeddc80d,
			0xe63fbaade147932f, 0xe7bc5f3155cf018f, 0xfea81c7885a6b43a,
			0x953624adc666b026, 0xd938b76acaec07e7, 0xd29b9c1af7943184,
			0xc2a5f0fb1b33ee57, 0xed3875b982e7c010, 0x8000000000000000,
			0x8000000000000000, 0x8000000000000000, 0x0000000000000000};

	if (pow == 16)
		return (pow10_16);
	if (pow == 32)
		return (pow10_32);
	if (pow == 64)
		return (pow10_64);
	if (pow == 128)
		return (pow10_128);
	if (pow == 256)
		return (pow10_256);
	return (get_larger_pow10());
}

/*
** 10^225 = 10^(128 + 64 + 32 + 1) = 10^128 * 10^64 * 10^32 * 10
** Just keep every radix^pow_of_2 where 0 <= pow_of_2 < log_radix(vlq) and
** find the exponent to decompose it cleverly.
*/

t_vlq			ft_vlq_getpow10(t_u32 exp)
{
	t_vlq	result;
	t_u8	sub15_exp;

	if (exp >= 0x400)
	{
		result = ft_vlq_getpow10(exp - 512);
		ft_vlq_mul_acc(&result, get_larger_pow10());
		return (result);
	}
	sub15_exp = exp & 0xF;
	result = ft_vlqnew(1);
	result[0] = ft_ipowi(10, sub15_exp);
	if (exp & 0x10)
		ft_vlq_mul_acc(&result, get_large_pow10(16));
	if (exp & 0x20)
		ft_vlq_mul_acc(&result, get_large_pow10(32));
	if (exp & 0x40)
		ft_vlq_mul_acc(&result, get_large_pow10(64));
	if (exp & 0x80)
		ft_vlq_mul_acc(&result, get_large_pow10(128));
	if (exp & 0x100)
		ft_vlq_mul_acc(&result, get_large_pow10(256));
	if (exp & 0x200)
		ft_vlq_mul_acc(&result, get_large_pow10(512));
	return (result);
}
