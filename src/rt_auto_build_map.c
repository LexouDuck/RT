
# include <time.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# include "libft.h"
# include "libft_io.h"
# include "libft_list.h"
# include "libft_convert.h"
# include "libft_string.h"
# include "libft_memory.h"

# include "../rt.h"
# include "debug.h"
# include "rt_scene.h"

typedef struct 				s_float3
{
	t_float 	x;
	t_float 	y;
	t_float 	z;
}							t_float3;					


char						*t_float3_to_str
(							
							t_float3 *vector, 
							int i
)
{
	t_tuple	x;
	t_tuple	y;
	t_tuple	z;
	char	*result;

	x.items = ft_f32_to_str(vector->x, i);
	y.items = ft_f32_to_str(vector->y, i);
	z.items = ft_f32_to_str(vector->z, i);
	x.length = ft_strlen(x.items);
	y.length = ft_strlen(y.items);
	z.length = ft_strlen(z.items);
	if (!(result = (char *)malloc(x.length + y.length + z.length + 7)))
		return (NULL);
	i = 0;
	result[i++] = '(';
	if (ft_memcpy(result + i, x.items, x.length) && (i += x.length + 2))
		free(x.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, y.items, y.length) && (i += y.length + 2))
		free(y.items);
	ft_memcpy(result + i - 2, ", ", 2);
	if (ft_memcpy(result + i, z.items, z.length) && (i += z.length + 2))
		free(z.items);
	ft_memcpy(result + i - 2, ")\0", 2);
	return (result);
}






/*
**
**  ATTENTION A SUPPRIMER AU DESSUS
**
*/



typedef enum						e_random_type
{
	TYPE_FLOAT 	= 0,
	TYPE_PRIMITIVE,
	TYPE_MATERIAL,
	TYPE_COLOR,
	TYPE_BBOX,
	TYPE_POS_X,
	TYPE_POS_Y,
	TYPE_POS_Z,

}									t_random_type;



int									set_alea_nb
(
									t_random_type	type
)
{
	int result;

	if (type == TYPE_PRIMITIVE)
		result = ((rand() % 5) + 1);
	else if (type == TYPE_MATERIAL)
		result = (rand() % MATERIALS);
	else if (type == TYPE_FLOAT)
		result = (rand() % 20001) - 10000;
	else if (type == TYPE_COLOR)
		result = (rand() % 1000);
	else if (type == TYPE_BBOX)
		result = (rand() %  2001) - 1000;
	else if (type == TYPE_POS_X)
		result = (rand() %  1901) - 9500;
	else if (type == TYPE_POS_Y)
		result = (rand() % 4001);
	else if (type == TYPE_POS_Z)
		result = (rand() % 2001) - 1000;
	return (result);
}


/*
** this function select aleatory object's type
*/

void								write_enums
(
									int		fd
)
{
	char 	*primitives;

	primitives = rt_get_str_primitive(
		(t_primitive)set_alea_nb(TYPE_PRIMITIVE));
	FT_Write_String(fd, primitives);
	FT_Write_Char(fd, '\n');
	FT_Write_String(fd,"material:");
	FT_Write_String(fd, rt_get_str_material(
		(t_material)set_alea_nb(TYPE_MATERIAL)));
	FT_Write_Char(fd, '\n');
}

/*
** This function chose aleatory value to the object's vector
*/

t_float3							set_float3_nb(t_random_type type)
{
	t_float3 	nb;

	nb.x = set_alea_nb(type) / 1000.0;
	nb.y = set_alea_nb(type) / 1000.0;
	nb.z = set_alea_nb(type) / 1000.0;

	return (nb);
}

/*
** this is the principal corp of the file, this function print all item
*/

void								write_float3
(
									int 	fd, 
									char	*label,
									t_random_type type

)
{
	char			*tmp;
	t_float3		vector;

	FT_Write_String(fd, label);
	vector = set_float3_nb(type);
	if ((tmp = t_float3_to_str(&vector, 5)))
	{
		FT_Write_String(fd, tmp);
		free(tmp);
	}
	FT_Write_Char(fd, '\n');
}


void								build_fix_object
(
									int fd
)
{
	FT_Write_Line(fd, 	"SPHERE");
	FT_Write_Line(fd,	"material:LIGHT");
	FT_Write_Line(fd,	"color:(1.00000, 1.00000, 1.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(9.00000, 5.00000, 10.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");
		
	FT_Write_Line(fd, 	"SPHERE");
	FT_Write_Line(fd,	"material:LIGHT");
	FT_Write_Line(fd,	"color:(1.00000, 1.00000, 1.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(-9.00000, 5.00000, 10.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"CUBE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"\"floor\"");
	FT_Write_Line(fd,	"color:(0.26666, 0.26666, 0.26666)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(0.00000, -1.00000, 0.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(10.00000, -1.00000, 10.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"CUBE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"\"ceiling\"");
	FT_Write_Line(fd,	"color:(0.26666, 0.26666, 0.26666)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(0.00000, 11.00000, 0.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(10.00000, 2.00000, 10.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"CUBE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"\"walls back\"");
	FT_Write_Line(fd,	"color:(0.19999, 0.53333, 1.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(0.00000, 5.00000, -10.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(10.00000, 7.00000, 1.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"SPHERE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"color:(1.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(0.00000, 2.00000, 0.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(1.00000, 1.00000, 1.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"PLANE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"\"Walls left\"");
	FT_Write_Line(fd,	"color:(1.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(-9.50000, 4.50000, 0.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(0.50000, 5.00000, 10.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd, 	"PLANE");
	FT_Write_Line(fd,	"material:DIFFUSE");
	FT_Write_Line(fd,	"\"Walls right\"");
	FT_Write_Line(fd,	"color:(1.00000, 0.66666, 0.66666)");
	FT_Write_Line(fd,	"color2:(0.00000, 3.50000, 0.00000)");
	FT_Write_Line(fd,	"pos:(9.50000, 5.00000, 0.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"scale:(0.50000, 5.00000, 10.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");

	FT_Write_Line(fd,	"RECTANGLE");
	FT_Write_Line(fd,	"material:LIGHT");
	FT_Write_Line(fd,	"\"light of the top\"");
	FT_Write_Line(fd,	"color:(1.00000, 1.00000, 1.00000)");
	FT_Write_Line(fd,	"color2:(0.00000, 0.00000, 0.00000)");
	FT_Write_Line(fd,	"pos:(0.00000, 9.00000, -2.00000)");
	FT_Write_Line(fd,	"rot:(0.00000, 0.00000, -3.16000)");
	FT_Write_Line(fd,	"scale:(4.00000, 8.00000, 8.00000)");
	FT_Write_Line(fd,	"bbox_vi:(-1.00000, -1.00000, -1.00000)");
	FT_Write_Line(fd,	"bbox_vf:(1.00000, 1.00000, 1.00000)\n");
}


void								write_scene
(
									int fd
)
{
	int				i;
	char 			*vec;

	FT_Write_String(fd, "BG #");
	FT_Write_Line(fd, "808080");
	FT_Write_Char(fd, '\n');
	build_fix_object(fd);

	i = -1;
	while (++i < 7) 
	{
		write_enums(fd);
	
		write_float3(fd, "color:", TYPE_COLOR);
		write_float3(fd, "color2:", TYPE_COLOR);
		FT_Write_String(fd, "pos:(");
		vec = FT_F32_To_String(set_alea_nb(TYPE_POS_X) / 1000, 5);
		FT_Write_String(fd, vec);
		FT_Write_String(fd, ", ");
		vec = FT_F32_To_String(set_alea_nb(TYPE_POS_Y) / 1000, 5);
		FT_Write_String(fd, vec);
		FT_Write_String(fd, ", ");
		vec = FT_F32_To_String(set_alea_nb(TYPE_POS_Z) / 1000, 5);
		FT_Write_String(fd, vec);
		FT_Write_String(fd, ")\n");
		FT_Write_Line(fd, "rot:(0.00000 , 0.00000, 0.00000)");
		write_float3(fd, "scale:", TYPE_FLOAT);
		write_float3(fd, "bbox_vi:", TYPE_BBOX);
		write_float3(fd, "bbox_vf:", TYPE_BBOX);
		FT_Write_Char(fd, '\n');
	}
}

/*
** This function creat a file 
*/

int									auto_build_map
(
									char *filename
)
{

	int			fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filename, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	srand(time(NULL));
	write_scene(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filename, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (filename ? OK : ERROR);
}


int		main(int argc, char **argv)
{
	int 		i;

	
	if (argc == 2)
	{
		if (auto_build_map(argv[1]) == ERROR)
			return (ERROR);
	}
	else
	{
		debug_output("Donne un nom de fichier comme parametre\n");
		return (OK);
	}
	return (OK);
}