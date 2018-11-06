/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FT_GetNextLine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft_io.h"
#include "../../libft_string.h"

static	void	GNL_DeleteListItem(t_list **store, int fd, char **line)
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

static	int		GNL_ReadFile(t_list *elem)
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

static	int		GNL_MakeLine(t_list *elem, char **line)
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

int				FT_GetNextLine(int const fd, char **line)
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
	if (GNL_ReadFile(elem) < 0)
		return (GNL_ERROR);
	if (*(char *)elem->content == '\0')
	{
		GNL_DeleteListItem(&store, fd, line);
		return (GNL_END);
	}
	if (GNL_MakeLine(elem, line) < 0)
		return (GNL_ERROR);
	return (GNL_LINE);
}
