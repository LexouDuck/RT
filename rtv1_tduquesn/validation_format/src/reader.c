/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 06:00:02 by fulguritu         #+#    #+#             */
/*   Updated: 2018/10/06 12:58:48 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_bool		read_rt_file_context_line2(t_control *ctrl,
												char const *str, int fd)
{
	if (ft_strnequ(str, "TRIANGLE", 8))
		r_rt_f_set_obj(ctrl, fd, triangle);
	else if (ft_strnequ(str, "PARABOLOID", 10))
		r_rt_f_set_obj(ctrl, fd, paraboloid);
	else if (ft_strnequ(str, "SADDLE", 6))
		r_rt_f_set_obj(ctrl, fd, saddle);
	else if (ft_strnequ(str, "CUBE", 4))
		r_rt_f_set_obj(ctrl, fd, cube);
	else
		return (FALSE);
	return (TRUE);
}

static void			read_rt_file_context_line(t_control *ctrl,
												char const *str, int fd)
{
	if (ft_strnequ(str, "LIGHT", 5))
		r_rt_f_setup_light(ctrl, fd);
	else if (ft_strnequ(str, "PLANE", 5))
		r_rt_f_set_obj(ctrl, fd, plane);
	else if (ft_strnequ(str, "SPHERE", 6))
		r_rt_f_set_obj(ctrl, fd, sphere);
	else if (ft_strnequ(str, "INFCONE", 7))
		r_rt_f_set_obj(ctrl, fd, infcone);
	else if (ft_strnequ(str, "INFCYLINDER", 11))
		r_rt_f_set_obj(ctrl, fd, infcylinder);
	else if (ft_strnequ(str, "CYLINDER", 8))
		r_rt_f_set_obj(ctrl, fd, cylinder);
	else if (ft_strnequ(str, "DISK", 4))
		r_rt_f_set_obj(ctrl, fd, disk);
	else if (ft_strnequ(str, "SQUARE", 6))
		r_rt_f_set_obj(ctrl, fd, square);
	else if (ft_strnequ(str, "CONE", 4))
		r_rt_f_set_obj(ctrl, fd, cone);
	else if (ft_strnequ(str, "CAMERA", 6))
		r_rt_f_set_cam(ctrl, fd);
	else if (read_rt_file_context_line2(ctrl, str, fd))
		return ;
	else
		exit_error("read_rt_file_context_line: invalid context str error", 0);
}

/*
** Entity refers to both objects, light sources, or camera setup
*/

static t_bool		read_rt_entity_block(t_control *ctrl, int const fd)
{
	char		*str;
	int			status;

	str = NULL;
	if ((status = get_next_line(fd, &str)) == ERR_RD)
		exit_error("read_rt_file: gnl: error while reading line", errno);
	else if (status == EOF_RD || !str)
		return (TRUE);
	read_rt_file_context_line(ctrl, str, fd);
	ft_strdel(&str);
	if ((status = get_next_line(fd, &str)) == EOF_RD)
		return (TRUE);
	if (status == ERR_RD || !ft_strequ(str, ""))
		exit_error("r_rt_f_setup_light: missing newline after object, camera,"
					" or light block", errno);
	ft_strdel(&str);
	return (FALSE);
}

void				read_rt_file(t_control *ctrl, char const *fpath)
{
	int			fd;
	int			i;

	if ((fd = open(fpath, O_RDONLY)) == -1)
		exit_error("open: file couldn't be opened", errno);
	i = -1;
	while (++i < MAX_FILE_LN_NB)
	{
		if (read_rt_entity_block(ctrl, fd))
			break ;
	}
	if (ctrl->objlst_len == 0 || ctrl->objlst_len == 0)
		exit_error("read_rt_file: missing object or light in file", 0);
	if (close(fd) == -1)
		exit_error("close: file closed improperly", errno);
}
