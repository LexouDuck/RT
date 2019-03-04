
# include "debug.h"
# include <time.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "SDL.h"
# include "libft.h"

#define TYPE_OBJ 	1
#define TYPE_FLOAT 	0

int						set_alea_nb
(
						bool	type,
						int		nb
)
{
	srand(time(NULL));
	if (type == TYPE_OBJ)
	{
		nb = rand()%116;
		return (nb);
	}
	else if (type == TYPE_FLOAT)
	{
		nb = rand()%11;
		return (nb);

	}
	//ou 1 seule return(nb);
}


/*
** this function select aleatory object's type
*/

void					set_objtype
(
						int		fd
)
{
	int		nb;
	int		i;

	i = 7;
	while (i >= 0)
	{

		srand(time(NULL));
		nb = rand()%116;
		if (nb >= 0 && nb <= 15)
		{
			FT_Write_String(fd, "Sphere");
		}
		else if (nb > 15 && nb <= 30)
		{	
			FT_Write_String(fd, "Cube");
		}
		else if (nb > 30 && nb <= 45)
		{
			FT_Write_String(fd, "Cone");
		}
		else if (nb > 45 && nb <= 60)
		{
			FT_Write_String(fd, "Cylinder");
		}
		else if (nb > 60 && nb <= 75)
		{
			FT_Write_String(fd, "hyperboloid");
		}
		else if (nb > 75 && nb <= 100)
		{
			FT_Write_String(fd, "Paraboloid");
		}
		else //(nb > 100 && nb <= 115)
		{
			FT_Write_String(fd, "Infcone");
		}
		--i;
	}
}

/*
** This function chose aleatory value to the object's vector
*/

int							set_float3_nb
(
							int 	x,
							int		y,
							int		z
)
{
	int 	*nb;

	nb[0] = chose_alea_nb(TYPE_FLOAT, nb);
	nb[1] = chose_alea_nb(TYPE_FLOAT, nb);
	nb[2] = chose_alea_nb(TYPE_FLOAT, nb);

	return (nb[0], nb[1], nb[2]);
}


/*
** this is the principal corp of the file, this function print all item
*/

void						print_map
(
							int fd
)
{
	int		x;
	int		y;
	int		z;


	FT_Write_String(fd, "BG #")
	FT_Write_String(fd, "808080");

	set_objtype(fd);
	FT_Write_String(fd,"material:");


	
	FT_Write_String(fd, "color:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");

	FT_Write_String(fd, "pos:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");

	FT_Write_String(fd, "rot:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");

	FT_Write_String(fd, "scale:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");

	FT_Write_String(fd, "bbox_vi:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");

	FT_Write_String(fd, "bbox_vf:");
	set_float3_nb(x, y, z);
	FT_Write_String("(%d, %d, %d)");
}

/*
** This function creat a file 
*/

int								auto_build_map
(
								char *filename
)
{

	int			fd;

	fd = open(filename, O_WRONLY |/* O_TRUNC |*/ O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filename, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	print_map(fd);
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
		#!/bin/bash
		Name=$(argv[1])
		filename="${Name}.rt"
		num=0
		while [ -f $filename ]; do       //??
	    filename="${name}-${num}.txt"	
		done
		touch $filename

		auto_build_map(filename)
	}
	else
	{
		//debug_output_value("Donne un nom de fichier comme parametre:");
		printf("Donne un nom de fichier comme parametre:");
		return (0);
	}
	return (0);
}