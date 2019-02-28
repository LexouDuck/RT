
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
		if (object)
		{

			debug_output("Sphere ");
		}
		i++;
	}
}