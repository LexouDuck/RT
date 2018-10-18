/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:36:44 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/21 15:15:54 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			del_t_str(void *content, size_t content_size)
{
	t_str	*tstr;

	if (content)
	{
		tstr = (t_str*)content;
		ft_strdel(&(tstr->data));
		ft_delete(content, content_size);
	}
}

static void		handle_color_t_str(t_str *a_t_str)
{
	ft_strreplace_inplace(&(a_t_str->data), STR_BOLD, BOLD);
	ft_strreplace_inplace(&(a_t_str->data), STR_UNDERLINE, UNDERLINE);
	ft_strreplace_inplace(&(a_t_str->data), STR_BLACK, C_BLACK);
	ft_strreplace_inplace(&(a_t_str->data), STR_RED, C_RED);
	ft_strreplace_inplace(&(a_t_str->data), STR_GREEN, C_GREEN);
	ft_strreplace_inplace(&(a_t_str->data), STR_YELLOW, C_YELLOW);
	ft_strreplace_inplace(&(a_t_str->data), STR_BLUE, C_BLUE);
	ft_strreplace_inplace(&(a_t_str->data), STR_MAGENTA, C_MAGENTA);
	ft_strreplace_inplace(&(a_t_str->data), STR_CYAN, C_CYAN);
	ft_strreplace_inplace(&(a_t_str->data), STR_WHITE, C_WHITE);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_BLACK, BG_BLACK);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_RED, BG_RED);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_GREEN, BG_GREEN);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_YELLOW, BG_YELLOW);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_BLUE, BG_BLUE);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_MAGENTA, BG_MAGENTA);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_CYAN, BG_CYAN);
	ft_strreplace_inplace(&(a_t_str->data), STR_BG_WHITE, BG_WHITE);
	ft_strreplace_inplace(&(a_t_str->data), STR_RESET, RESET);
	a_t_str->len = ft_strlen(a_t_str->data);
}

t_str			*str_to_t_str(char const *str)
{
	t_str	*result;

	if (!(result = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	if (!str)
	{
		result->data = NULL;
		result->len = -1;
		return (result);
	}
	else
	{
		result->data = ft_strdup(str);
		result->len = ft_strlen(str);
	}
	if (ft_strfind(str, '{') < ft_strfind(str, '}'))
		handle_color_t_str(result);
	return (result);
}

static void		t_str_append(void *s1, void *s2)
{
	int		len;
	char	*tmp;
	t_str	*acc;
	t_str	*next;

	if (!s1 || !s2)
		return ;
	acc = (t_str*)s1;
	next = (t_str*)s2;
	if (!(next->data) || next->len == -1)
	{
		ft_strdel(&(next->data));
		next->data = ft_strdup(next->len == -1 ? "(error)" : "(null)");
		next->len = 6 + (next->len == -1);
	}
	len = acc->len + next->len;
	tmp = ft_strnew(len);
	ft_memcpy(tmp, acc->data, acc->len);
	ft_memcpy(tmp + acc->len, next->data, next->len);
	free(acc->data);
	acc->len = len;
	acc->data = tmp;
}

t_str			to_single_t_str(t_list *lststr)
{
	t_str	acc;

	acc.data = ft_strnew(0);
	acc.len = 0;
	ft_lstfold(lststr, &acc, &t_str_append);
	return (acc);
}
