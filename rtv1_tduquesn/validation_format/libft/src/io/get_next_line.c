/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:40:28 by tduquesn          #+#    #+#             */
/*   Updated: 2018/03/01 19:37:23 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_fd_info	*get_fd_info(t_list **a_fd_info_lst, int const fd)
{
	t_fd_info	*fdi;
	t_list		*cur_elem;

	cur_elem = *a_fd_info_lst;
	while (cur_elem)
	{
		if (cur_elem->content && ((t_fd_info*)cur_elem->content)->fd == fd)
			return ((t_fd_info*)cur_elem->content);
		cur_elem = cur_elem->next;
	}
	if (!(fdi = (t_fd_info*)malloc(sizeof(t_fd_info))))
		return (NULL);
	fdi->fd = fd;
	fdi->bufoffset = 0;
	fdi->rdlen = -1;
	ft_bzero(fdi->buf, BUFF_SIZE + 1);
	ft_lstappend(a_fd_info_lst, ft_lstnew_no_copy(fdi, sizeof(t_fd_info)));
	cur_elem = ft_lstget(*a_fd_info_lst, ft_lstsize(*a_fd_info_lst) - 1);
	return ((t_fd_info*)cur_elem->content);
}

static int			bnl_part(t_fd_info *fdi, char **line, char **str)
{
	if (fdi->bufoffset == 0)
	{
		if ((fdi->rdlen = read(fdi->fd, fdi->buf, BUFF_SIZE)) == -1)
			return (ERR_RD);
		else if (fdi->rdlen == 0 && !*line)
		{
			if (*line)
				ft_strdel(line);
			return (EOF_RD);
		}
		else if (fdi->rdlen == 0 && *line)
			return (NWL_RD);
	}
	if (!(*str = ft_strcdup(fdi->buf + fdi->bufoffset, '\n')))
		return (ERR_RD);
	fdi->bufoffset += ft_strlen(*str);
	*line = ft_strappend(line, *str);
	if (fdi->rdlen == 1 && BUFF_SIZE != 1 && fdi->buf[0] == '\n')
		return (NWL_RD);
	return (2);
}

static int			build_next_line(t_fd_info *fdi, char **line)
{
	char	*str;
	int		status;

	str = NULL;
	fdi->bufoffset = fdi->bufoffset % BUFF_SIZE;
	while (!str)
	{
		if ((status = bnl_part(fdi, line, &str)) != 2)
			return (status);
		if (fdi->buf[fdi->bufoffset] == '\n' && fdi->rdlen == BUFF_SIZE)
			break ;
		if (fdi->buf[fdi->bufoffset] == '\n' && !fdi->buf[fdi->bufoffset + 1])
			fdi->bufoffset += 1;
		if (fdi->buf[fdi->bufoffset] == '\0')
		{
			ft_strdel(&str);
			fdi->bufoffset = 0;
			ft_bzero(fdi->buf, BUFF_SIZE);
		}
	}
	ft_strdel(&str);
	fdi->bufoffset += 1;
	return (NWL_RD);
}

int					get_next_line(int const fd, char **line)
{
	static t_list	*fd_info_lst = NULL;
	t_fd_info		*fdi;
	int				status;
	t_list			*tmp_elem;
	t_u32			i;

	fdi = get_fd_info(&fd_info_lst, fd);
	if (!line || fd < 0)
		return (ERR_RD);
	*line = NULL;
	status = build_next_line(fdi, line);
	tmp_elem = fd_info_lst;
	i = 0;
	if (status == EOF_RD)
		while (tmp_elem)
		{
			if (((t_fd_info*)(tmp_elem->content))->fd == fdi->fd)
			{
				ft_lstpop(&fd_info_lst, i, ft_delete);
				break ;
			}
			++i;
			tmp_elem = tmp_elem->next;
		}
	return (status);
}
