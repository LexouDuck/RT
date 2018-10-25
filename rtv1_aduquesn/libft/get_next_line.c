/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	gnl_delete_listelem(t_list **store, int fd, char **line)
{
	t_list	*lst;
	t_list	*result;

	*line = NULL;
	result = NULL;
	lst = *store;
	while (lst)
	{
		if (lst->next && (int)lst->next->content_size == fd)
		{
			result = lst->next;
			lst->next = result->next;
			break ;
		}
		lst = lst->next;
	}
	if (result)
	{
		free(result->content);
		free(result);
		result = NULL;
	}
}

static	int		gnl_read_file(t_list *elem)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*temp;

	buffer[BUFF_SIZE] = '\0';
	while (!ft_strchr(elem->content, '\n') &&
		(result = read((int)elem->content_size, buffer, BUFF_SIZE)) > 0)
	{
		temp = (char *)elem->content;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(elem->content = ft_strjoin(temp, buffer)))
			return (0);
		free(temp);
	}
	return (result);
}

static	int		gnl_make_line(t_list *elem, char **line)
{
	size_t	length;
	size_t	space;
	char	*str;

	length = ft_strlen(elem->content);
	str = elem->content;
	space = (size_t)ft_strchr(str, '\n');
	space = space ? (size_t)((char *)space - str) : length;
	*line = ft_strsub(elem->content, 0, space);
	if (space == length)
	{
		ft_strclr(elem->content);
		return (GNL_LINE);
	}
	str = NULL;
	if (!(str = (char *)malloc(length + 1)))
		return (GNL_ERROR);
	ft_strcpy(str, (char *)elem->content + space + 1);
	ft_strclr(elem->content);
	ft_strcpy(elem->content, str);
	free(str);
	return (GNL_LINE);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*store = NULL;
	t_list			*elem;

	if (line == NULL || BUFF_SIZE < 0 || fd < 0)
		return (GNL_ERROR);
	if (!store && !(store = ft_lstnew(NULL, fd)))
		return (GNL_ERROR);
	elem = store;
	while (elem && (int)elem->content_size != fd)
		elem = elem->next;
	if (!elem)
		ft_lstadd(&store, (elem = ft_lstnew(NULL, fd)));
	if (!elem->content && !(elem->content = ft_strnew(2)))
		return (GNL_ERROR);
	if (gnl_read_file(elem) < 0)
		return (GNL_ERROR);
	if (*(char *)elem->content == '\0')
	{
		gnl_delete_listelem(&store, fd, line);
		return (GNL_END);
	}
	if (gnl_make_line(elem, line) < 0)
		return (GNL_ERROR);
	return (GNL_LINE);
}

char			*read_file(int const fd)
{
	int		result;
	char	buffer[BUFF_SIZE + 1];
	char	*file;
	char	*temp;

	file = ft_strnew(1);
	buffer[BUFF_SIZE] = '\0';
	while ((result = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		temp = file;
		if (result < BUFF_SIZE)
			buffer[result] = '\0';
		if (!(file = ft_strjoin(temp, buffer)))
			return (NULL);
		free(temp);
	}
	if (result < 0)
	{
		if (file)
			free(file);
		return (NULL);
	}
	return (file);
}
