#include "../rt.h"
#include "debug.h"



void	print_map()
{
	FT_Write_String(fd, "BG #")
	FT_Write_String("color:");
	
	FT_Write_String("pos:");
	FT_Write_String("rot:");
	FT_Write_String("scale:");
	FT_Write_String("bbox_vi:");
	FT_Write_String("bbox_vf:");

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