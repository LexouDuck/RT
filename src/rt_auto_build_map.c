#include "../rt.h"
#include "debug.h"
#include <time.h>

#define type_obj 1
#define type_float3 0

void	chose_alea_nb(bool	type, int	nb)
{
	srand(time(NULL));
	if (type == type_obj)
	{
		nb = rand()%116;
	}
	else if (type == type_float3)
	{
		nb.x = rand()%11;

	}
}

void	chose_objtype()
{
	int		nb;

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
	else
	{
		FT_Write_String(fd, "Infcone");
	}
}

void	print_map()
{
	FT_Write_String(fd, "BG #")
	FT_Write_String(fd, "808080");

	chose_objtype();

	FT_Write_String(fd, "color:");

	FT_Write_String(fd, "pos:");
	FT_Write_String(fd, "rot:");
	FT_Write_String(fd, "scale:");
	FT_Write_String(fd, "bbox_vi:");
	FT_Write_String(fd, "bbox_vf:");

}

int		auto_build_map(char *filename)
{

	int			fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		debug_output_value("Error: Could not write RT file: ", filepath, FALSE);
		debug_output_value("open() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	rt_save(fd);
	if (close(fd) < 0)
	{
		debug_output_value("Error: Could not close RT file: ", filepath, FALSE);
		debug_output_value("close() -> ", strerror(errno), FALSE);
		return (ERROR);
	}
	return (filepath ? OK : ERROR);
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
		while [ -f $filename ]; do
	    	num=$(( $num + 1 ))
	    filename="${DATE}-${num}.txt"
		done
		touch $filename
	}
	else
	{
		debug_output_value("Donne un nom de fichier comme parametre:");
		return (0);
	}
	return (0)
}