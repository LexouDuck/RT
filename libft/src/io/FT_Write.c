/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/ft_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"

inline void	ft_write_char(char c, int fd)
{
	write(fd, &c, 1);
}

inline void	ft_write_str(const char *str, int fd)
{
	if (str)
	{
		write(fd, str, ft_strlen(str));
	}
}

inline void	ft_write_line(const char *str, int fd)
{
	if (str)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

void		ft_write_strls(const char **strls, int fd)
{
	int i;

	if (!strls)
		return ;
	i = 0;
	while (strls[i])
	{
		write(fd, strls[i], ft_strlen(strls[i]));
		write(fd, "\n", 1);
		++i;
	}
}

void		ft_write_memory(const char *str, t_u8 cols, int fd)
{
	/* TODO
	char	*tmp;
	char	**tmp_strls;
	t_u8	wordlen;
	*/
	if (!str || cols == 0 || fd < 0)
		return ;
	/*
	tmp = ft_strhex(str);
	wordlen = 4;
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
	*/
}
