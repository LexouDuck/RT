
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
	TYPE_OBJ 	= 1,
	TYPE_FLOAT 	= 0
}									t_random_type;



int									set_alea_nb
(
									t_random_type	type,
									int				nb
)
{
	if (type == TYPE_OBJ)
		nb = rand() % 116;
	else if (type == TYPE_FLOAT)
		nb = (rand() % 21) - 10;
	return (nb);
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
		(t_primitive)((rand() % 5) + 1));
	FT_Write_String(fd, primitives);
	FT_Write_Char(fd, '\n');
	FT_Write_String(fd,"material:");
	FT_Write_String(fd, rt_get_str_material(
		(t_material)(rand() % MATERIALS)));
	FT_Write_Char(fd, '\n');
}

/*
** This function chose aleatory value to the object's vector
*/

t_float3							set_float3_nb
(
									t_float 	x,
									t_float		y,
									t_float		z
)
{
	t_float3 	nb;

	nb.x = set_alea_nb(TYPE_FLOAT, nb.x);
	nb.y = set_alea_nb(TYPE_FLOAT, nb.y);
	nb.z = set_alea_nb(TYPE_FLOAT, nb.z);

	return (nb);
}

/*
** this is the principal corp of the file, this function print all item
*/

void								write_float3
(
									int 	fd, 
									char	*label
)
{
	char			*tmp;
	t_float3		vector;

	FT_Write_String(fd, label);
	set_float3_nb(vector.x, vector.y, vector.z);
	if ((tmp = t_float3_to_str(&vector, 5)))
	{
		FT_Write_String(fd, tmp);
		free(tmp);
	}
	FT_Write_Char(fd, '\n');
}

void								write_scene
(
									int fd
)
{
	int				i;

	FT_Write_String(fd, "BG #");
	FT_Write_Line(fd, "808080");
	FT_Write_Char(fd, '\n');

	i = -1;
	while (++i < 7) 
	{
		write_enums(fd);
	
		write_float3(fd, "color:");
		write_float3(fd, "color_b:");
		write_float3(fd, "pos:");
		write_float3(fd, "rot:");
		write_float3(fd, "scale:");
		write_float3(fd, "bbox_vi:");
		write_float3(fd, "bbox_vf:");
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