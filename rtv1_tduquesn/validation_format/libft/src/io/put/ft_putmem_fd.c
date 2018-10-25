/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 06:56:13 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:13:16 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_io.h"
#include "libft_str.h"

void		ft_putmem_fd(char const *str, int fd)
{
	char	*tmp;
	char	**tmp_strls;
	t_u8	wordlen;
	t_u8	cols;

	if (!str || fd < 0)
		return ;
	tmp = ft_strhex(str);
	wordlen = 4;
	cols = HEXCOLS;
	tmp_strls = ft_strdivide(tmp, 2);
	ft_strdel(&tmp);
	tmp = ft_strlsjoin((char const **)tmp_strls, " ");
	ft_strlsdel(&tmp_strls);
	tmp_strls = ft_strdivide(tmp, 3 * wordlen);
	ft_strdel(&tmp);
	tmp = ft_strlsjoin((char const **)tmp_strls, " ");
	ft_strlsdel(&tmp_strls);
	tmp_strls = ft_strdivide(tmp, (3 * wordlen + 1) * cols);
	ft_strdel(&tmp);
	tmp = ft_strlsjoin((char const **)tmp_strls, "\n");
	ft_putendl(tmp);
	ft_strdel(&tmp);
	ft_strlsdel(&tmp_strls);
}
