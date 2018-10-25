/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 06:21:52 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/24 06:21:58 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LST_H
# define LIBFT_LST_H

# include "libft.h"
# include "libft_mem.h"

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;

/*
** ============= List Functions =============
*/

/*
** Allocates and returns a new element of a list, according to the given
** arguments. Note that 'content' is duplicated.
*/
t_list					*ft_lstnew(void const *content, size_t content_size);

/*
** Same as lstnew except content is not duplicated.
*/
t_list					*ft_lstnew_no_copy(void *content, size_t content_size);

/*
** Inserts a new element of a list 'new' at the pointer '*alst', chaining it
** with the next element.
*/
void					ft_lstadd(t_list **alst, t_list *new_elem);

/*
** Appends the element 'new_elem' to the end of the list starting at '*alst'.
*/
void					ft_lstappend(t_list **alst, t_list *new_elem);

/*
** Deletes the given element pointed to by 'alst' with the given function 'del',
** then frees memory and NULLs '*alst'.
*/
void					ft_lstdelone(t_list **alst,
									void (*del)(void *, size_t));

/*
** Deletes all the elements in the list starting at '*alst', calls 'del' and
** frees memory for each, and lastly NULLs '*alst'.
*/
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** Returns the amount of elements in the given list 'lst'.
*/
t_u32					ft_lstsize(t_list *lst);

/*
** Removes and frees the first occurence of elem in a linked list and relinks
** the remaining strands.
*/
void					ft_lstpop(t_list **a_lst, t_u32 index,
									void (*del)(void *, size_t));

/*
** Returns a newly allocated copy of lst.
*/
t_list					*ft_lstcpy(t_list *lst);

/*
** Returns a newly allocated copy of a section of lst. Returns NULL if error.
*/
t_list					*ft_lstsub(t_list *lst, t_u32 start, t_u32 n);

/*
** Returns the pointer to the element at index n in linked list lst.
*/
t_list					*ft_lstget(t_list *lst, t_u32 n);

/*
** Iterates on the given list 'lst', applying the given function 'f' to each
** of its elements.
*/
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));

/*
** Creates a new list which is the result of applying the given function 'f'
** to each element of 'lst'.
*/
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Applies operator f to the elements of lst by pairs, grinding the list into
** a single value. Here, the left operand acc is an accumulator (starting at
** the unit element for the operand type of f, like 0 for addition or "" for
** concatenation) of the results of previous iterations of f and the right
** operand is the next item in lst. The point of this function is to turn an
** associative binary operator (like +(x,y):=x + y) into an efficient n-ary
** operator (like SUM_1..n(x_i)). Note that typeof(acc), and typeof(f_arg1)
** should be the same type 'a; also, that typeof(lst->content) and
** typeof(f_arg2) should be of the same type 'b. You can make this work
** with 'a != 'b.
*/
void					ft_lstfold(t_list *lst, void *acc,
									void (*f)(void *, void *));

/*
** Useful conversion function. Must be sure to take a valid list of strings.
** Should log inoherence in size/null-term.
*/
char					**ft_lststr_to_strls(t_list	*lst);

/*
** === List IO ===
*/
/*
** Writes the data contained in elem to standard output as a stream of t_u8.
*/
void					ft_putlstelem(t_list *elem);

/*
** Writes the data contained in each elem of lst to standard output.
*/
void					ft_putlst(t_list *lst);

/*
** Writes the data contained in elem to file descriptor as a stream of t_u8.
*/
void					ft_putlstelem_fd(t_list *elem, int fd);

/*
** Writes the data contained in each elem of lst to file descriptor as
** streams of t_u8 separated by newlines.
*/
void					ft_putlst_fd(t_list *lst, int fd);

/*
** Writes an element of a linked list containing signed numbers of any size_t
** (1, 2, 4 or 8) to file descriptor fd. If content_size is not appropriate,
** nothing is done and the function fails silently.
*/
void					ft_putnbr_lstelem_fd(t_list *elem, int fd);

/*
** Writes a linked list containing signed numbers of any size_t (1, 2, 4 or 8)
** to file descriptor fd.
*/
void					ft_putnbr_lst_fd(t_list *lst, int fd);

#endif
