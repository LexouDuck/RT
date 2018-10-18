/*
** mlx.h for MinilibX
**
** Made by Charlie Root
** Login   <ol@epitech.net>
**
** Started on  Mon Jul 31 16:37:50 2000 Charlie Root
** Last update Tue May 15 16:23:28 2007 Olivier Crouzet
*/

/*
**		+----------+
**		| MinilibX |  (Please report bugs)
**		+----------+
**	MiniLibX  is an easy way to create graphical software,
**	without any prior X-Window programming knowledge.
**	It provides some simple functions for window creation,
**	drawing pixels or text onto windows, image rendering,
**	as well as some basic events management.
*/
/*
**	MinilibX uses 2 libraries that you must link when compiling:
**	-lmlx -lXext -lX11
**	(for 'libmlx.a', 'libXext.a' and 'libX11.a' respectively)
**	You may also need to specify the path to these libraries.
**	Do this by using the -L compiler flag (usually at /usr/lib).
*/
/*
**	MinilibX provides an implementation of Xpm image loading.
**	Please note however that this implementation is incomplete.
**	Merci de communiquer tout probleme de chargement d'image de ce type.
*/

#ifndef MLX_H
# define MLX_H

/*
**	Sets up the graphical subsystem for MinilibX.
**  A call to this function is needed before everything else.
**  returns (void *)0 if failed
*/
void			*mlx_init();

/*
** === Window functions ===
*/

/*
**	Opens a new X window of the given size, with the given title.
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- size_x:	the horizontal size of the window (in pixels)
**	- size_y:	the vertical size of the window (in pixels)
**	- title:	the title to give to this new window
**  returns (void *)0 if failed
*/
void			*mlx_new_window(
	void *mlx_ptr,
	int size_x,
	int size_y,
	char const *title);
/*
**	Clears the entire window, setting every pixel to black
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- win_ptr:	the identifier returned by mlx_new_window()
**  return is not important
*/
int				mlx_clear_window(
	void *mlx_ptr,
	void *win_ptr);
/*
**	Closes the given window
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- win_ptr:	the identifier returned by mlx_new_window()
**  return is not important
*/
int				mlx_destroy_window(
	void *mlx_ptr,
	void *win_ptr);

/*
** === Drawing functions ===
*/

/*
**	Sets the pixel at the given coordinates to the given color
**  The origin for 'x' and 'y' is the top-left corner of the window
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- win_ptr:	the identifier returned by mlx_new_window()
**	- x:		the horizontal coordinate of the pixel to set
**	- y:		the vertical coordinate of the pixel to set
**	- color:	the color to set (format is 32-bit: 0x00RRGGBB)
**  return is not important ?
*/
int				mlx_pixel_put(
	void *mlx_ptr,
	void *win_ptr,
	int x,
	int y,
	int color);
/*
**	Displays the given text at the given coordinates (in the given color)
**  The origin for 'x' and 'y' is the top-left corner of the window
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- win_ptr:	the identifier returned by mlx_new_window()
**	- x:		the horizontal coordinate of the text
**	- y:		the vertical coordinate of the text
**	- color:	the color to set (format is 32-bit: 0x00RRGGBB)
**	- string:	the text to display
**  return is not important ?
*/
int				mlx_string_put(
	void *mlx_ptr,
	void *win_ptr,
	int x,
	int y,
	int color,
	char *string);

/*
** === Image functions ===
*/

/*
**	Allocates memory for a 'width'x'height' bitmap.
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- width:	the horizontal size of the image
**	- height:	the vertical size of the image
**  returns an identifier needed to manipulate the image later
*/
void			*mlx_new_image(
	void *mlx_ptr,
	int width,
	int height);
/*
**	Destroys the given image.
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- img_ptr:	the identifier of the image
**  returns 0 if the image was successfully destroyed
*/
int				mlx_destroy_image(
	void *mlx_ptr,
	void *img_ptr);
/*
**	Returns info about the created image, allowing the user to modify the image.
**	The three last parameters should be the addresses of three different ints.
**	- img_ptr:			the identifier of the image
**	- bits_per_pixel:	the amount of bits needed to store a color of this image
**	- size_line:		the amount of bytes needed to store 1 line of this image
**	- endian:			0 means the X-server is little-endian, 1 = big endian
**  returns a pointer to the stored pixel data. This means that you
**	can use 'bits_per_pixel' and 'size_line' to read any pixel from the image.
*/
char			*mlx_get_data_addr(
	void *img_ptr,
	int *bits_per_pixel,
	int *size_line,
	int *endian);
/*
**	Displays the given image onto the given window, at the given coordinates
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- win_ptr:	the identifier returned by mlx_new_window()
**	- img_ptr:	the identifier of the image
**	- x:		the horizontal coordinate at which to show the image
**	- y:		the vertical coordinate at which to show the image
*/
int				mlx_put_image_to_window(
	void *mlx_ptr,
	void *win_ptr,
	void *img_ptr,
	int x,
	int y);
/*
**	Depending on the display, the number of bits used to store a pixel
**		color can change.
**	The most common is 32-bit RGB mode, using one byte for each color channel.
**	This must be converted to fit the bits_per_pixel requirement of the
**		image at hand, and make the color format understandable to the
**		underlying X-Server.
**	- mlx_ptr:	the identifier returned by mlx_init()
**	- color:	the color value to convert
**	returns the 'bpp' least significant bits of the given color value
*/
unsigned int	mlx_get_color_value(
	void *mlx_ptr,
	int color);
/*
**	These 2 functions will create a new image in the same way.
**	They will fill it using the specified 'xpm_data' or 'filename'.
**	Note that MiniLibX does not use the standard Xpm library to deal
**		with xpm images.
**	As such, you may not be able to read all types of xpm images.
**	This function does, however, handle transparency.
**	They both return the identifer for this newly loaded image
*/
void			*mlx_xpm_to_image(
	void *mlx_ptr,
	char **xpm_data,
	int *width,
	int *height);
void			*mlx_xpm_file_to_image(
	void *mlx_ptr,
	char const *filename,
	int *width,
	int *height);

/*
** === Event functions ===
*/

/*
**	The infinite loop function, this call should never return.
**	It serves to suspend the program as it waits for events to occur.
**	- mlx_ptr:	the identifier returned by mlx_init()
**	returns 1 if an error occurred ?
*/
int				mlx_loop(void *mlx_ptr);
/*
**	These 4 functions work in the exact same way.
**	'key' is for any keyboard events, 'mouse' for mouse events
**	'loop' when there is no event, and 'expose' when the window is redrawn
**	They set up the event checking, and  ld bbe called before mlx_loop()
**	- win_ptr:		the identifier returned by mlx_new_window()
**					(note that the event is specific to this window)
**	- funct_ptr:	the pointer to the function you wish to call when an event
**					occurs.
**	- param:		this will be passed to the function everytime it is called,
**					and should be used to store any parameters it might need
*/
int				mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(), void *param);
int				mlx_key_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_mouse_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int				mlx_expose_hook(void *win_ptr, int (*funct_ptr)(), void *param);
/*
**	The user-side event handling functions are defined thusly:
**	(the names given here are arbitrary, you can name them however you want)
**	- int event_loop(void *param);
**	- int event_expose(void *param);
**	- int event_mouse(int button, int x,int y, void *param);
**	- int event_key(int keycode, void *param);
*/

/*
**	???
*/
int				mlx_do_sync(void *mlx_ptr);
/*
** Disables the keyboard's auto-repeat.
*/
int				mlx_do_key_autorepeatoff(void *mlx_ptr);
/*
** Enables the keyboard's auto-repeat feature.
*/
int				mlx_do_key_autorepeaton(void *mlx_ptr);

/*
**  A generic hook system for any X event,
**	and MinilibX functions that can be hooked.
**	You will have to use the macros and  defines
**	from '.../X11/X.h' for the 2 'x_' arguments.
**	- win_ptr:	the identifier returned by mlx_new_window()
**	- x_event:	the event code to handle
**	- x_mask:	the bitmask of the event to handle
**	- funct:	pointer to the handling function
**	- param:	this will be passed to the function everytime it is called,
**				and should be used to store any parameters it might need
*/
int				mlx_hook(
	void *win_ptr,
	int x_event,
	int x_mask,
	int (*funct)(),
	void *param);

#endif
