/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:32:49 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/25 19:29:39 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MEM_H
# define LIBFT_MEM_H

# include "libft.h"

# define _MSB_ 			0x8000000000000000
# define _NOT_MSB_		0x7FFFFFFFFFFFFFFF
# define _ALLBITS_		0xFFFFFFFFFFFFFFFF

/*
** ============ Memory Functions ===========
*/

/*
** Allocates 'size' bytes in memory, returning the pointer at which said bytes
** were allocated, or NULL if the memory could not be allocated.
*/
void					*ft_memalloc(size_t size);

/*
** Frees the allocated memory at '**ptr', and sets '*ptr' as NULL.
*/
void					ft_memdel(void **ptr);

/*
** Swaps the two numbers pointed to by 'ptr1' and 'ptr2' (they must both be
** of the same 'size').
*/
int						ft_swap(void *a, void *b, size_t sizeof_ab);

/*
** Fills 'n' bytes of memory with 0s, starting at 'ptr'.
*/
void					ft_bzero(void *ptr, size_t n);

/*
** Fills 'n' bytes of memory with 'byte' (taking only the first 8 bits of this
** int arg), starting at 'ptr'.
*/
void					*ft_memset(void *ptr, int byte, size_t n);

/*
** Copies 'n' bytes of memory from 'src' to 'dest'.
*/
void					*ft_memcpy(void *dest, void const *src, size_t n);

/*
** Copies at most 'n' bytes of memory from 'src' to 'dest', stopping at the
** first encounter of a byte equal to 'c'.
*/
void					*ft_memccpy(void *dest, void const *src, int c,
									size_t n);

/*
** Reads 'n' bytes of memory from 'src' then writes those bytes to 'dest'
** - useful if 'src' and 'dest' overlap.
*/
void					*ft_memmove(void *dest, void const *src, size_t n);

/*
** Finds and returns the first occurrence of a byte equal to 'byte',
** starting at 'ptr' and searching 'n' bytes.
*/
void					*ft_memchr(void const *ptr, int byte, size_t n);

/*
** Compares 'n' bytes at 'ptr1' and 'ptr2', returning (byte1 - byte2)
** at the first difference encountered.
*/

int						ft_memcmp(void const *ptr1, void const *ptr2, size_t n);

/*
** Returns a newly allocated memory area which copy of the given memory area
** 'ptr' (or NULL if the required memory could not be allocated or if ptr is
** empty).
*/
void					*ft_memdup(void const *ptr, size_t n);

/*
** Returns a string in hexadecimal describing what is contained in memory
** pointed to by s. If n is larger than allocated area, behavior is undefined.
*/
char					*ft_memhex(void const *ptr, size_t n);

/*
** If p, clears memory over mem_size bytes then frees p and NULLs it.
*/
void					ft_delete(void *p, size_t mem_size);

/*
** Returns a value such that every bit b that is not at index i <= b < j is
** switched off. Returns -1 (ie, 0xFFF...FF) in case of error.
** TODO: make it work with a byte_len argument 1, 2, 4 or 8, like ft_swap ?
*/
t_u64					ft_u64bits_itoj(t_u64 ul, t_u8 i, t_u8 j);

/*
** Returns the number of lines in a nul-terminated strls, or just a general
** null-terminated pointer array.
*/
t_u32					ft_ptrarrlen(void const *a_ptrarr);

/*
** Returns a point to a numl-terminated, clear, pointer array of length n.
*/
void					*ft_ptrarrnew(t_u32 n);

/*
** Returns true iff the MSB is set to 1
*/
t_u64					ft_msb(t_u64 x);

/*
** Returns x with the sign bit flipped to 0
*/
t_u64					ft_not_msb(t_u64 x);

#endif
