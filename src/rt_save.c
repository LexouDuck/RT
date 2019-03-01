
#include "../rt.h"
#include "debug.h"
#include "libft_convert.h"

void		rt_save(int fd)
{
	size_t 			i;
	t_object* 		object;
	char*			tmp;

	i = 0;
	if ((tmp = FT_U32_To_HexString(rt.scene.bg_color)))
	{	
		FT_Write_String(fd, "BG #");
		FT_Write_Line(fd, tmp);
		FT_Write_Char(fd, '\n');
	}
	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
		if (object)
		{
			
			if ((tmp = rt_get_str_primitive(object->type)))
			{
				FT_Write_Line(fd, tmp);
		
			}
			if ((tmp = rt_get_str_material(object->material)))
			{
				FT_Write_String(fd,"material:");
				FT_Write_Line(fd, tmp);
			}
			if ((tmp = cl_float3_to_str(&object->rgb, 5)))
			{
				FT_Write_String(fd, "color:");
				FT_Write_Line(fd, tmp);
				free(tmp);
			}
			if ((tmp = cl_float3_to_str(&object->pos, 5)))
			{
				FT_Write_String(fd, "pos:");
				FT_Write_Line(fd, tmp);
				free(tmp);
			}
			if ((tmp = cl_float3_to_str(&object->rot, 5)))
			{
				FT_Write_String(fd, "rot:");
				FT_Write_Line(fd, tmp);
				free(tmp);
			}
			if ((tmp = cl_float3_to_str(&object->scale, 5)))
			{
				FT_Write_String(fd, "scale:");
				FT_Write_Line(fd, tmp);
				free(tmp);
			}
			if (ft_strlen(object->name))
			{
				FT_Write_Char(fd, '"');
				FT_Write_String(fd, object->name);
				FT_Write_Char(fd, '"');
				FT_Write_Char(fd, '\n');
			}
			FT_Write_Char(fd, '\n');

		}
		i++;
	}
	FT_Write_Char(fd, '\n');

}
