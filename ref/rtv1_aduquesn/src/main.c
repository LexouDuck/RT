/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

/*
**static void	rtv1_printdebug(t_rtv1 *rtv1)
**{
**	t_object *object;
**	t_light *light;
**	t_list *lst;
**
**	ft_putendl("RTV1 File successfully read:");
**	ft_putstr("BG Color: "); ft_putendl(ft_itoa_hex(rtv1->bg_color, "#"));
**	ft_putendl("Lights:");
**	lst = rtv1->lights;
**	while (lst)
**	{
**		light = (t_light *)lst->content;
**		ft_putstr(ft_itoa_hex(light->color, "\t#"));
**		ft_putstr(", ");
**		ft_putstr(ft_itoa(light->strength));
**		ft_putstr(", (");
**		ft_putstr(ft_ftoa(light->position.x, 6)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(light->position.y, 6)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(light->position.z, 6)); ft_putstr(")\n");
**		lst = lst->next;
**	}
**	ft_putendl("Objects:");
**	lst = rtv1->objects;
**	while (lst)
**	{
**		object = (t_object *)lst->content;
**		static const char *types[6] = {
**			"N/A", "SPHERE  ", "CYLINDER", "CUBE    ", CONE    "};
**		ft_putstr(types[(int)object->type]);
**		ft_putstr(ft_itoa_hex(object->color, "-> #")); ft_putstr(",\t(");
**		ft_putstr(ft_ftoa(object->position.x, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->position.y, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->position.z, 3)); ft_putstr(")\t{");
**		ft_putstr(ft_ftoa(object->rotation.x, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->rotation.y, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->rotation.z, 3)); ft_putstr("}\t[");
**		ft_putstr(ft_ftoa(object->scale.x, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->scale.y, 3)); ft_putstr(", ");
**		ft_putstr(ft_ftoa(object->scale.z, 3)); ft_putstr("]\n");
**		lst = lst->next;
**	}
**}
*/

/*
**	else rtv1_printdebug(rtv1);
*/

static int	rtv1_init(t_rtv1 *rtv1, int fd)
{
	t_parser	parser;
	char		*error;

	rtv1->camera = NULL;
	rtv1->lights = NULL;
	rtv1->objects = NULL;
	if ((error = rtv1_read_file(rtv1, &parser, fd)))
	{
		ft_putstr("Error: while reading rt file -> at line ");
		ft_putnbr(parser.line);
		ft_putstr(":\n");
		ft_putendl(error);
		free(error);
		return (ERROR);
	}
	if (!(rtv1->camera = camera_new()))
	{
		ft_putendl("Error: could not initialize the camera");
		return (ERROR);
	}
	return (OK);
}

static int	rtv1_init_objects(t_list *lst)
{
	t_object	*object;
	int			(*intersect[5])(t_object *, t_ray *);
	void		(*getnormal[5])(t_vector *, t_object *, t_vector *);

	intersect[0] = NULL;
	intersect[1] = intersect_sphere;
	intersect[2] = intersect_cylinder;
	intersect[3] = intersect_cube;
	intersect[4] = intersect_cone;
	getnormal[0] = NULL;
	getnormal[1] = getnormal_sphere;
	getnormal[2] = getnormal_cylinder;
	getnormal[3] = getnormal_cube;
	getnormal[4] = getnormal_cone;
	while (lst)
	{
		if (!(object = (t_object *)lst->content))
			return (ERROR);
		object->intersect = intersect[(int)object->type];
		object->getnormal = getnormal[(int)object->type];
		vector_scale(&object->rotation, M_PI / 180);
		lst = lst->next;
	}
	return (OK);
}

static int	img_init(t_mlx *mlx)
{
	t_image	*image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (ERROR);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	image->buffer = (t_u8 *)mlx_get_data_addr(mlx->img_ptr,
		&(image->bpp),
		&(image->line),
		&(image->endian));
	mlx->image = image;
	return (OK);
}

static int	open_window(t_rtv1 *rtv1, char *title)
{
	t_mlx	mlx;

	mlx.rtv1 = rtv1;
	if (!(mlx.mlx_ptr = mlx_init()))
	{
		ft_putendl("Error: could not initialize MinilibX");
		return (ERROR);
	}
	if (img_init(&mlx))
	{
		ft_putendl("Error: could not create render image");
		return (ERROR);
	}
	if (!(mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, title)))
	{
		ft_putendl("Error: could not open new window");
		return (ERROR);
	}
	render(&mlx, mlx.rtv1->camera);
	setup_events(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (OK);
}

int			main(int argc, char **argv)
{
	t_rtv1	rtv1;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putendl("Error: could not open file");
			return (ERROR);
		}
		if (rtv1_init(&rtv1, fd))
			return (ERROR);
		if (rtv1_init_objects(rtv1.objects))
			return (ERROR);
		if (open_window(&rtv1, ft_strjoin("RTV1 - ", argv[1])))
			return (ERROR);
		return (OK);
	}
	ft_putendl("rtv1: expecting one file as argument");
	return (ERROR);
}
