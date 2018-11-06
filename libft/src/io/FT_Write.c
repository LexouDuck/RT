/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/FT_Write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"

inline void	FT_WriteChar(char c, int fd)
{
	write(fd, &c, 1);
}

inline void	FT_WriteString(const char *str, int fd)
{
	if (str)
		write(fd, str, FT_StringLength(str));
}

inline void	FT_WriteLine(const char *str, int fd)
{
	if (str)
	{
		write(fd, str, FT_StringLength(str));
		write(fd, "\n", 1);
	}
}

void		FT_WriteStringArray(const char **strls, int fd)
{
	int i;

	if (!strls)
		return ;
	i = 0;
	while (strls[i])
	{
		write(fd, strls[i], FT_StringLength(strls[i]));
		write(fd, "\n", 1);
		++i;
	}
}

void		FT_WriteMemory(const char *str, t_u8 cols, int fd)
{
	/*
	char	*tmp;
	char	**tmp_strls;
	t_u8	wordlen;
	*/
	if (!str || cols == 0 || fd < 0)
		return ;
	/*
	tmp = FT_strhex(str);
	wordlen = 4;
	tmp_strls = FT_strdivide(tmp, 2);
	FT_strdel(&tmp);
	tmp = FT_strlsjoin((char const **)tmp_strls, " ");
	FT_strlsdel(&tmp_strls);
	tmp_strls = FT_strdivide(tmp, 3 * wordlen);
	FT_strdel(&tmp);
	tmp = FT_strlsjoin((char const **)tmp_strls, " ");
	FT_strlsdel(&tmp_strls);
	tmp_strls = FT_strdivide(tmp, (3 * wordlen + 1) * cols);
	FT_strdel(&tmp);
	tmp = FT_strlsjoin((char const **)tmp_strls, "\n");
	FT_putendl(tmp);
	FT_strdel(&tmp);
	FT_strlsdel(&tmp_strls);
	*/
}
