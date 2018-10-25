/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:07:23 by tduquesn          #+#    #+#             */
/*   Updated: 2018/03/01 19:52:52 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft_str.h"
# include "libft_lst.h"

/*
** Note that read()'s behavior at EOF is to not change the buffer and return 0.
** The last char read is not EOF but the last char itself. Say we have a buffer
** filled with 1s, and read is called with rdlen < bufsize. Then there won't
** even be a '\0' to separate what has just been read from the 1s.
**
** Also, as long as read() returns something else than 0, even if it is a
** single '\n', it must return NWL_RD, even if the return string is empty.
*/

# define BUFF_SIZE 4096
# define NWL_RD 1
# define EOF_RD 0
# define ERR_RD -1

/*
** Stores info of a current file description being sequentially read.
** - fd :        the open file descriptor
** - rdlen :     length of the last call to "read" (useful for EOF checks)
** - buf :       the statically allocated buffer containing the current data
**                 being read - may contain multiple newlines or none.
** - bufoffset : offset of the readhead in buf
*/

typedef struct		s_fd_info
{
	int			fd;
	int			rdlen;
	char		buf[BUFF_SIZE + 1];
	size_t		bufoffset;
}					t_fd_info;

int					get_next_line(int const fd, char **line);

#endif
