/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduquesn <AlexisDuquesne@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by aduquesn          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by aduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void		shader_diffuse(
	t_shader *shader,
	t_light *light)
{
	float	tmp;

	tmp = vector_scalar(&shader->ray.dir, &shader->hit_normal) * shader->norm;
	if (tmp < 0)
		tmp = 0;
	tmp *= 1 / M_PI;
	tmp *= light->strength;
	vector_set(&shader->diffuse,
		shader->diffuse.x + shader->light.x * tmp,
		shader->diffuse.y + shader->light.y * tmp,
		shader->diffuse.z + shader->light.z * tmp);
}

static void		shader_specular(
	t_shader *shader,
	t_ray *ray)
{
	float	tmp;

	tmp = 2 * vector_scalar(&shader->ray.dir, &shader->hit_normal);
	shader->ray.dir.x += shader->hit_normal.x * tmp;
	shader->ray.dir.y += shader->hit_normal.y * tmp;
	shader->ray.dir.z += shader->hit_normal.z * tmp;
	tmp = -vector_scalar(&shader->ray.dir, &ray->dir);
	if (tmp < 0)
		tmp = 0;
	tmp /= shader->ray.t;
	vector_set(&shader->specular,
		shader->specular.x + shader->light.x * tmp,
		shader->specular.y + shader->light.y * tmp,
		shader->specular.z + shader->light.z * tmp);
}

static t_u32	shader_getcolor(
	t_u32 color,
	t_vector *diffuse,
	t_vector *specular)
{
	int	r;
	int	g;
	int	b;

	r = (int)((float)color_get_r(color) * diffuse->x + specular->x);
	g = (int)((float)color_get_g(color) * diffuse->y + specular->y);
	b = (int)((float)color_get_b(color) * diffuse->z + specular->z);
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (color_new(0, r, g, b));
}

void			shader_setupray(t_shader *shader, t_light *light)
{
	vector_set(&shader->ray.dir,
		light->position.x - shader->hit_pos.x,
		light->position.y - shader->hit_pos.y,
		light->position.z - shader->hit_pos.z);
	vector_set(&shader->light,
		(float)color_get_r(light->color),
		(float)color_get_g(light->color),
		(float)color_get_b(light->color));
	shader->norm = vector_length(&shader->ray.dir);
	shader->ray.t = sqrt(shader->norm);
	shader->norm = 1 / shader->norm;
	vector_scale(&shader->ray.dir, 1 / shader->ray.t);
}

t_u32			render_shade(t_rtv1 *rtv1, t_ray *ray, t_shader *shader)
{
	int			render;
	t_list		*lst;
	float		tmp;

	render = rtv1->camera->render;
	tmp = (render & RENDER_DIFFUSE) ? 0.2 : 1;
	vector_set(&shader->diffuse, tmp, tmp, tmp);
	vector_set(&shader->specular, 0, 0, 0);
	shader->ray.pos = shader->hit_pos;
	lst = rtv1->lights;
	while (lst)
	{
		shader_setupray(shader, (t_light *)lst->content);
		if (!(render & RENDER_SHADOWS) ||
			!(render_trace(rtv1, &shader->ray, shader->ray.t, NULL)))
		{
			if (render & RENDER_DIFFUSE)
				shader_diffuse(shader, (t_light *)lst->content);
			if (render & RENDER_SPECULAR)
				shader_specular(shader, ray);
		}
		lst = lst->next;
	}
	return (shader_getcolor(shader->object_color,
		&shader->diffuse, &shader->specular));
}
