/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LIST_H
# define LIBFT_LIST_H

# include "libft.h"

/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef struct			s_uple
{
	void				*elements;
	size_t				elem_size;
	size_t				length;
}						t_uple;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

/*
** Allocates and returns a new element of a list,
** according to the given arguments.
*/
t_list	*ft_lstnew(void const *content, size_t content_size);

/*
** Inserts a new element of a list 'elem' at the pointer '*alst',
** chaining this new element with the next element of this list.
*/
void	ft_lstadd(t_list **alst, t_list *elem);

/*
** Appends the element 'new_elem' to the end of the list starting at '*alst'.
** If 'alst' is NULL, it will create
*/
void	ft_lstappend(t_list **alst, t_list *elem);

/*
** Deletes the given element pointed to by 'alst' with the function 'del',
** and then frees memory and sets '*alst' as a NULL pointer.
*/
void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

/*
** Deletes all the elements in the list starting at '*alst',
** calls 'del' and frees memory for each, and lastly sets '*alst' as NULL.
*/
void	ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** ************************************************************************** *|
**                                 List Checks                                *|
** ************************************************************************** *|
*/

/*
** Returns the amount of elements in the given list 'lst'.
*/
int		ft_lstsize(t_list *lst);

/*
** Returns the 'index'th element in the given list 'alst'.
** Will return NULL if 'index' is beyond the last element.
*/
t_list	*ft_lstget(t_list **alst, t_u32 index);

/*
** ************************************************************************** *|
**                             Other List Operations                          *|
** ************************************************************************** *|
*/

/*
** Returns a subsection of the given list 'alst',
** starting at 'index' and copying 'length' elements.
** Will return NULL if 'index' is too large or length is 0.
** If 'index' is valid but the list is not large enough for 'length',
** then the resulting list will have fewer than 'length' elements.
*/
t_list	**ft_lstsub(t_list **alst, t_u32 index, t_u32 length);

/*
** Iterates upon each element of the given list 'lst',
** applying the given function 'f' to each of its elements.
*/
void	ft_lstiter(t_list *lst, void (*f)(t_list *));

/*
** Creates a new list which is the result of applying
** the given function 'f' to each element of 'lst'.
*/
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));

/*
** Creates a new contiguous array from the given linked list.
** Returns NULL if elements of 'alst' are of unequal size.
** The array will be terminated with the value pointed to by
** the given 'terminator' pointer (or not, if pointer is NULL).
*/
void	*ft_array_fixed(t_list **alst, void *terminator);

/*
** Creates a new jagged array (2d) from the given linked list.
** The top-level pointer array is null-terminated.
*/
void	**ft_array(t_list **alst);

#endif
