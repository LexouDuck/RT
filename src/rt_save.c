
#include "../rt.h"
#include "debug.h"

void		rt_save(int fd)
{
	size_t 			i;
	t_object* 		object;
//	t_primitive 	primitive = NULL;
	char*			type;
	char*			material;
	char*			color;
	char*			pos;
	char*			rot;
	char*			scale;

	i = 0;
	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
		if (object)
		{
			type = rt_get_str_primitive(object->type);
			material = rt_get_str_material(object->material);
			color = cl_float3_to_str(&object->rgb, 5);
			pos = cl_float3_to_str(&object->pos, 5);
			rot = cl_float3_to_str(&object->rot, 5);
			scale = cl_float3_to_str(&object->scale, 5);

			FT_Write_Line(fd, type);
			FT_Write_String(fd,"material:");
			FT_Write_Line(fd, material);
			FT_Write_String(fd, "color:");
			FT_Write_Line(fd, color);
			FT_Write_String(fd, "pos:");
			FT_Write_Line(fd, pos);
			FT_Write_String(fd, "rot:");
			FT_Write_Line(fd, rot);
			FT_Write_String(fd, "scale:");
			FT_Write_Line(fd, scale);
			FT_Write_Char(fd, '\n');
		}
		i++;
	}
	free(color);
	free(pos);
	free(rot);
	free(scale);

}
