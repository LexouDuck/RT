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
**                                  Macros                                    *|
** ************************************************************************** *|
*/

#define FT_ListNew(item, size)				ft_lstnew(item, size)
#define FT_ListAdd(alst, elem)				ft_lstadd(alst, elem)
#define FT_ListAppend(alst, elem)			ft_lstappend(alst, elem)
#define FT_ListInsert(alst, elem, index)	ft_lstinsert(alst, elem, index)
#define FT_ListRemove(alst, f)				ft_lstdelone(alst, f)
#define FT_ListDelete(alst, f)				ft_lstdel(alst, f)

#define FT_ListSize(lst)					ft_lstsize(lst)
#define FT_ListGet(alst, index)				ft_lstget(alst, index)
#define FT_ListFind(lst, query)				ft_lstfind(lst, query)

#define FT_ListSub(alst, index, n)			ft_lstsub(alst, index, n)
#define FT_ListIterate(lst, f)				ft_lstiter(lst, f)
#define FT_ListMap(lst, f)					ft_lstmap(lst, f)
#define FT_ListToTuple(alst)				ft_array_fixed(alst)
#define FT_ListToArray(alst)				ft_array(alst)



/*
** ************************************************************************** *|
**                                 Definitions                                *|
** ************************************************************************** *|
*/

typedef struct			s_tuple
{
	void				*items;
	size_t				item_size;
	size_t				length;
}						t_tuple;

typedef struct			s_list
{
	void				*item;
	size_t				item_size;
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

typedef void (*f_list_delete)(void *, size_t);
typedef void (*f_list_iterate)(t_list *);
typedef t_list *(*f_list_map)(t_list *);

/*
** ************************************************************************** *|
**                             Basic List Operations                          *|
** ************************************************************************** *|
*/

/*
**	Allocates and returns a new element of a list,
**	according to the given arguments.
*/
t_list	*ft_lstnew(void const *item, size_t size);

/*
**	Inserts a new element of a list 'elem' at the pointer '*alst',
**	chaining this new element with the next element of this list.
*/
void	ft_lstadd(t_list **alst, t_list *elem);

/*
**	Appends the element 'elem' to the end of the list starting at '*alst'.
**	If '*alst' is NULL, it'll append 'elem' at index 0, creating a 1-elem list.
*/
void	ft_lstappend(t_list **alst, t_list *elem);

/*
**	Inserts the given element 'elem' at the given 'index' of the list '*alst'.
*/
void	ft_lstinsert(t_list **alst, t_list *elem, t_u32 index);

/*
**	Deletes the given element pointed to by 'alst' with the function 'f',
**	and then frees memory and sets '*alst' as a NULL pointer.
*/
void	ft_lstdelone(t_list **alst, void (*f)(void *, size_t));

/*
**	Deletes all the elements in the list starting at '*alst',
**	calls 'f' and frees memory for each, and lastly sets '*alst' as NULL.
*/
void	ft_lstdel(t_list **alst, void (*f)(void *, size_t));

/*
** ************************************************************************** *|
**                                 List Checks                                *|
** ************************************************************************** *|
*/

/*
**	Returns the amount of elements in the given list 'lst'.
*/
t_u32	ft_lstsize(t_list *lst);

/*
**	Returns the 'index'th element in the given list 'alst'.
**	Will return NULL if 'index' is beyond the last element.
*/
t_list	*ft_lstget(t_list **alst, t_u32 index);

/*
**	Returns the first encountered element of 'lst' for which lst.item == 'query'
*/
t_list	*ft_lstfind(t_list *lst, void const* query);

/*
** ************************************************************************** *|
**                             Other List Operations                          *|
** ************************************************************************** *|
*/

/*
**	Returns a subsection of the given list 'alst',
**	starting at 'index', and copying 'n' list elements.
**	Will return NULL if 'index' is too large or if 'n' is 0.
**	If 'index' is valid but the list is not large enough for 'n',
**	then the resulting list will have fewer than 'n' elements.
*/
t_list	**ft_lstsub(t_list **alst, t_u32 index, t_u32 n);

/*
**	Iterates upon each element of the given list 'lst',
**	applying the given function 'f' to each of its elements.
*/
void	ft_lstiter(t_list *lst, void (*f)(t_list *));

/*
**	Creates a new list which is the result of applying
**	the given function 'f' to each element of 'lst'.
*/
t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *));

/*
**	Creates a new contiguous memory array from the given linked list.
**	Returns NULL if any elements of '*alst' are of unequal size.
*/
t_tuple	*ft_lst_to_tuple(t_list **alst);

/*
**	Creates a new jagged array (2D pointer array) from the given list '*alst'.
**	The top-level pointer array is terminated by a NULL pointer.
*/
void	**ft_lst_to_array(t_list **alst);

#endif
