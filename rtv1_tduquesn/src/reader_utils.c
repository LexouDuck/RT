/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 09:10:13 by fulguritu         #+#    #+#             */
/*   Updated: 2019/01/09 07:14:18 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void			r_rt_f_read_vec3_line(t_vec_3d res, int fd)
{
	char		**strls;
	int			status;
	char		*line;

	line = NULL;
	if ((status = get_next_line(fd, &line)) == ERR_RD)
		exit_error("r_rt_f_read_vec3_line: gnl: error reading line", errno);
	else if (status == EOF_RD)
		exit_error("r_rt_f_read_vec3_line: EOF reached prematurely", 0);
	strls = ft_split(line, " \t");
	if (ft_ptrarrlen(strls) < 3)
		exit_error("r_rt_f_read_vec3_line: line must have 3 params", 0);
	res[0] = ft_atolf(strls[0]);
	res[1] = ft_atolf(strls[1]);
	res[2] = ft_atolf(strls[2]);
	ft_strlsdel(&strls);
	ft_strdel(&line);
	if (res[0] != res[0] || res[1] != res[1] || res[2] != res[2])
		exit_error("r_rt_f_read_vec3_line: param in vec3 line is NaN", 0);
}
/*
void				r_rt_f_setup_lightobj(t_control *ctrl, int fd)
{
	char	*line;
	t_float	tmp;
	int		status;

	line = NULL;
	r_rt_f_read_vec3_line(ctrl->spotlst[ctrl->spotlst_len].pos, fd);
	r_rt_f_read_vec3_line(ctrl->spotlst[ctrl->spotlst_len].rgb, fd);
	if (!ft_float_in_interval(ctrl->spotlst[ctrl->spotlst_len].rgb[0], 0., 1.)
	|| !ft_float_in_interval(ctrl->spotlst[ctrl->spotlst_len].rgb[1], 0., 1.)
	|| !ft_float_in_interval(ctrl->spotlst[ctrl->spotlst_len].rgb[2], 0., 1.))
		exit_error("r_rt_f_setup_light: light rgb should be in [0., 1.]^3", 0);
	if ((status = get_next_line(fd, &line)) == ERR_RD)
		exit_error("r_rt_f_setup_light: gnl: error reading line", errno);
	else if (status == EOF_RD)
		exit_error("r_rt_f_setup_light: EOF reached prematurely", 0);
	tmp = ft_atolf(line);
	if (tmp != tmp)
		exit_error("r_rt_f_setup_light: light intensity is NaN", 0);
	ft_strdel(&line);
	ctrl->spotlst[ctrl->spotlst_len].intensity = tmp;
	++(ctrl->spotlst_len);
	if (ctrl->spotlst_len > MAX_LGT_NB)
		exit_error("r_rt_f_setup_light: MAX_LGT_NB exceeded", 0);
}
*/
void				r_rt_f_set_obj(t_control *ctrl, int fd, t_objtype type)
{
	t_material	material;
	char		*line;
	t_s8		status;
	int			*len;
	t_object	*cur_obj;
	t_float		tmp;

	line = NULL;
	if ((status = get_next_line(fd, &line)) == ERR_RD)
		exit_error("r_rt_f_set_obj: gnl: error reading line", errno);
	else if (status == EOF_RD)
		exit_error("r_rt_f_set_obj: EOF reached prematurely", 0);
	material = ft_atoi(line);
	ft_strdel(&line);
	len = material == lightsrc ? &(ctrl->spotlst_len) : &(ctrl->objlst_len);
	cur_obj = material == lightsrc ? &(ctrl->spotlst[*len]) :
									&(ctrl->objlst[*len]); 
	r_rt_f_read_vec3_line(cur_obj->pos, fd);
	r_rt_f_read_vec3_line(cur_obj->scl, fd);
	r_rt_f_read_vec3_line(cur_obj->rot, fd);
	r_rt_f_read_vec3_line(cur_obj->rgb.vec, fd);
	r_rt_f_read_vec3_line(cur_obj->specul, fd);
	if (!ft_float_in_interval(cur_obj->rgb.val.r, 0., 1.)
	|| !ft_float_in_interval(cur_obj->rgb.val.g, 0., 1.)
	|| !ft_float_in_interval(cur_obj->rgb.val.b, 0., 1.))
		exit_error("r_rt_f_set_obj: obj rgb should be in [0., 1.] ^ 3", 0);


	if ((status = get_next_line(fd, &line)) == ERR_RD)
		exit_error("r_rt_f_set_obj: gnl: error reading line", errno);
	else if (status == EOF_RD)
		exit_error("r_rt_f_set_obj: EOF reached prematurely", 0);
	tmp = ft_atolf(line);
	if (tmp != tmp)
		exit_error("r_rt_f_set_obj: light intensity is NaN", 0);
	ft_strdel(&line);
	ctrl->spotlst[ctrl->spotlst_len].intensity = tmp;


cur_obj->refrac = material == glassy ? 1.5 : 1.;
//cur_obj->intensity = 1.;//default intensity for non-light sources, or maybe add a reflectivity variable ?

	build_obj(cur_obj, type, material);
	++(*len);
	if (*len >= (material == lightsrc ? MAX_LGT_NB : MAX_OBJ_NB))
		exit_error("r_rt_f_set_obj: MAX_OBJ/LGT_NB exceeded", 0);
}

void				r_rt_f_set_cam(t_control *ctrl, int fd)
{
	r_rt_f_read_vec3_line(ctrl->cam.anchor, fd);
	r_rt_f_read_vec3_line(ctrl->cam.polar_pos, fd);
}
