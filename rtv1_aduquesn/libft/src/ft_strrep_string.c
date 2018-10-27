/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 02:08:15 by aduquesn          #+#    #+#             */
/*   Updated: 2017/12/22 05:45:56 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static char		*ft_strrep_string_getresult(
	char const *str,
	t_list *matches,
	const t_uple *old,
	const t_uple *new)
{
	char	*result;
	t_list	*match;
	size_t	old_i;
	size_t	new_i;

	if (!(result = (char *)malloc(new->length + 1)))
		return (NULL);
	old_i = 0;
	new_i = 0;
	match = matches;
	while (str[old_i])
	{
		if (match && old_i == match->content_size)
		{
			ft_memcpy(result + new_i, new->elements, new->elem_size);
			match = match->next;
			new_i += new->elem_size;
			old_i += old->elem_size;
		}
		else
			result[new_i++] = str[old_i++];
	}
	result[new_i] = '\0';
	return (result);
}

char			*ft_strrep_string(
		char const *str,
		char *old_str,
		char *new_str)
{
	t_list	*matches;
	char	*match;
	size_t	length;
	t_uple	new;
	t_uple	old;

	matches = NULL;
	match = ft_strstr(str, old_str);
	while (match)
	{
		ft_lstappend(&matches, ft_lstnew(match, (size_t)(match - str)));
		match = ft_strstr(match + 1, old_str);
	}
	if (matches == NULL)
		return (ft_strdup(str));
	new.elements = new_str;
	old.elements = old_str;
	new.elem_size = ft_strlen(new_str);
	old.elem_size = ft_strlen(old_str);
	length = ft_lstsize(matches);
	length = ft_strlen(str) + length * (new.elem_size - old.elem_size);
	new.length = length;
	return (ft_strrep_string_getresult(str, matches, &old, &new));
}
/*
**	if (str == NULL || old == NULL || new == NULL)
**		return (NULL);
*/
