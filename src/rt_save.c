
#include "../rt.h"
#include "debug.h"

void		rt_save(int fd)
{
	size_t i;
	t_object* object;

	i = 0; 

	while (i < rt.scene.object_amount)
	{
		object = &rt.scene.objects[i];
/*		if (object)
		{
			if (select_type(object.type))
			
			cl_float3_to_str(cl_float3 *vector, int i);
		}
*/
		i++;
	}
}

/*
void	select_type(t_object object)
{
	t_primitive type;


	if ()	

}
*/