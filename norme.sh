#!/bin/sh

norminette src/*.c > norme_c.txt
norminette src/*.h > norme_h.txt
norminette *.h >> norme_h.txt
norminette libft/src/*/*.c > norme_libft_c.txt
norminette libft/*.h > norme_libft_h.txt
