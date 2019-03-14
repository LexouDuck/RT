NAME	=	RT

# Compiler
CC	= _
CC_WIN	= i686-w64-mingw32-gcc
CC_LIN	= gcc
CC_MAC	= gcc

# Compiler flags
CFLAGS	=	-Wall -Wextra -Werror $(CFLAGS_PLATFORM) -MMD -g

CFLAGS_PLATFORM = _
CFLAGS_WIN	= -mwindows -I./ -L./
CFLAGS_LIN	= -Wno-unused-result #-fsanitize=address -ldl
CFLAGS_MAC	= 

# Linker (for embedding binary files inside the program)
LD	= _
LD_WIN	= i686-w64-mingw32-ld -r -b binary
LD_LIN	= ld -r -b binary
LD_MAC	= ld -r -sectcreate __DATA __inc_ui_chr

# Libraries
LIBS		=	$(LIBFT) $(LIBSDL) $(OPENCL)
INCLUDE_DIRS =  -I$(LFTDIR) $(SDLHDRS)

LIBFT		=	-L$(LFTDIR) -lft
LIBSDL		= _
LIBSDL_WIN	= -L$(SDLDIR) -lSDL2
LIBSDL_LIN	= -L$(SDLDIR) -lSDL2 -lm
LIBSDL_MAC	= -L./SDL2.framework/Versions/Current -F. -framework SDL2

# Directories that this Makefile will use
SRCDIR	=	./src/
OBJDIR	=	./obj/
INCDIR	=	./inc/
LFTDIR	=	./libft/
SDLDIR	=	./
SDLHDRS	=	-I./SDL2-2.0.9/include/ -I./SDL2.framework/Headers/

# Set platform-specific variables
ifeq ($(OS),Windows_NT)
	OSFLAG := "WIN"
	CC := $(CC_WIN)
	LD := $(LD_WIN)
	LIBSDL := $(LIBSDL_WIN)
	CFLAGS_PLATFORM := $(CFLAGS_WIN)
	LIBS += -L./ -lOpenCL
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSFLAG := "LIN"
		CC := $(CC_LIN)
		LD := $(LD_LIN)
		LIBSDL := $(LIBSDL_LIN)
		CFLAGS_PLATFORM := $(CFLAGS_LIN)
		LIBS += -lOpenCL
		#ifeq ($(PROC_TYPE),)
		#	CFLAGS += -m32
		#else
		#	CFLAGS += -m64
		#endif
		# Check for Linux-AMD
		ifdef AMDAPPSDKROOT
		   INC_DIRS =. $(AMDAPPSDKROOT)/include
			ifeq ($(PROC_TYPE),)
				LIB_DIRS = $(AMDAPPSDKROOT)/lib/x86
			else
				LIB_DIRS = $(AMDAPPSDKROOT)/lib/x86_64
			endif
		else				
			# Check for Linux-Nvidia
			ifdef CUDA
			   INC_DIRS =. $(CUDA)/OpenCL/common/inc
			endif
		endif
	endif
	ifeq ($(UNAME_S),Darwin)
		OSFLAG := "MAC"
		CC := $(CC_MAC)
		LD := $(LD_MAC)
		LIBSDL := $(LIBSDL_MAC)
		CFLAGS_PLATFORM := $(CFLAGS_MAC)
		CFLAGS += -DMAC
		OPENCL := -framework OpenCL
	endif
endif



# List of C header files
HDRS	=	$(LFTDIR)libft.h 		\
			rt.h					\
			assets.h				\
			$(SRCDIR)debug.h		\
			$(SRCDIR)config.h		\
			$(SRCDIR)event.h		\
			$(SRCDIR)ui.h			\
			$(SRCDIR)rt_cl.h		\
			$(SRCDIR)rt_scene.h		\
			$(SRCDIR)rt_random.h	\

# List of C source code files
SRCS	= 	main.c							\
			init_sdl.c						\
			opencl_init.c					\
			opencl_utils.c					\
			opencl_memory.c					\
			opencl_kernels.c				\
			opencl_get_error_str.c			\
			opencl_render.c					\
			opencl_render_mem.c				\
			debug.c							\
			config.c						\
			config_ini.c					\
			config_access.c					\
			event.c							\
			event_window.c					\
			event_mouse.c					\
			event_key.c						\
			rt_get_str_scene.c				\
			rt_get_str_object.c				\
			rt_get_img_texture.c			\
			rt_file.c						\
			rt_open.c						\
			rt_open_util.c					\
			rt_open_read_materials.c		\
			rt_open_read_properties.c		\
			rt_open_read_textures.c			\
			rt_open_read_vectors.c			\
			rt_save.c						\
			rt_auto_build_scene.c			\
			rt_auto_build_scene_util.c		\
			rt_auto_build_cornellbox.c		\
			rt_random.c						\
			rt_random_util.c				\
			rt_scene.c						\
			rt_object.c						\
			camera.c						\
			update_window.c					\
			ui.c							\
			ui_init.c						\
			ui_init_mac.c					\
			ui_menu_file.c					\
			ui_menu_file_extra.c			\
			ui_menu_edit.c					\
			ui_render.c						\
			ui_render_util.c				\
			ui_render_util_rect.c			\
			ui_render_canvas.c				\
			ui_mouse.c						\
			ui_mouse_menu.c					\
			ui_mouse_objectlist.c			\
			ui_mouse_objectlist_enums.c		\
			ui_render_objectlist.c			\
			ui_control_numberbox_float.c	\
			ui_control_numberbox_int.c		\
			ui_control_textbox.c			\
			ui_scrollbar.c					\
			ui_prompt.c						\
			cl_float3_util.c

SRCDIR_CL	= $(SRCDIR)ocl/

# List of OpenCL source code files. ORDER MATTERS: FILES ARE CONCATENATED THEN READ.
SRCS_CL	=	rt_cl_scene.h.cl		\
			rt_cl_linear_algebra.cl	\
			rt_cl_random.cl			\
			rt_cl_materials.cl		\
			rt_cl_sphere.cl			\
			rt_cl_primitives_2d.cl	\
			rt_cl_cylinder.cl		\
			rt_cl_infcone.cl 		\
			rt_cl_cone.cl 			\
			rt_cl_cube.cl			\
			rt_cl_paraboloid.cl		\
			rt_cl_hyperboloid.cl 	\
			rt_cl_debug.cl			\
			rt_cl_build_scene.cl	\
			rt_cl_perlin_noise.cl	\
			rt_cl_patterns.cl		\
			rt_cl_texture.cl		\
			rt_cl_render.cl

# List of asset files to be embedded within the program
INCS	=	ui.chr



# define colors for terminal output
RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

# define object list and dependency files (.d)
OBJS	=	${SRCS:%.c=$(OBJDIR)%.o}
DEPENDS	=	${OBJS:.o=.d}



all: libraries $(NAME)

$(OBJS): | objdir

$(NAME): $(OBJS) $(HDRS) assets.o concat.cl
	@printf "Compiling program: "$@" -> "
	@$(CC) $(CFLAGS) $(OBJS) assets.o -o $@ $(LIBS)
	@if [ $(OSFLAG) = "MAC" ]; then \
		install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @executable_path/SDL2.framework/Versions/A/SDL2 $@; \
	fi
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(OBJDIR)%.o : $(SRCDIR)%.c $(HDRS)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS) -MF $(OBJDIR)$*.d
	@printf $(GREEN)"OK!"$(RESET)"\n"


CL_FILES	=	$(addprefix $(SRCDIR_CL), $(SRCS_CL))

concat.cl: $(CL_FILES)
	@export CL_LOG_ERRORS="stdout"
	@printf "Concatenating .cl files: "$@" -> "
	@cat $(CL_FILES) > $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

ASSET_FILES	=	$(addprefix $(INCDIR),$(INCS))

assets.o : $(ASSET_FILES)
	@printf "Compiling assets: "$@" -> "
	@if [ $(OSFLAG) = "MAC" ]; then \
		gcc -c empty.c -o $@; \
		$(LD) $(ASSET_FILES) $@ -o $@; \
	else \
		$(LD) $(ASSET_FILES) -o $@; \
	fi
	@printf $(GREEN)"OK!"$(RESET)"\n"

objdir:
	@mkdir -p $(OBJDIR)

libraries:
	@make -C $(LFTDIR) all

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)
	@rm -f log.txt
	@rm -f config.ini
	@rm -f assets.o
	@rm -f concat.cl

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: "$(NAME)"\n"
	@rm -f $(NAME)

rclean:
	@make -C $(LFTDIR) rclean
	@printf "Deleting obj folder...\n"
	@rm -rf $(OBJDIR)

re: fclean all



replace:
	@sed -i -e "s|$(old)|$(new)|g" $(addprefix $(SRCDIR), $(SRCS)) $(addprefix $(HDRDIR), $(HDRS))
	@printf "Replaced all instances of \'"$(old)"\' with \'"$(new)"\'.\n"

rename:
	@sed -i -e "s|\<$(old)\>|$(new)|g" $(addprefix $(SRCDIR), $(SRCS)) $(addprefix $(HDRDIR), $(HDRS))
	@printf "Renamed all words matching \'"$(old)"\' with \'"$(new)"\'.\n"



PREPROCESSED	=	${SRCS:%.c=$(OBJDIR)%.c}

preprocessed: $(PREPROCESSED)
	@printf "Outputting preprocessed code...\n"

$(OBJDIR)%.c : $(SRCDIR)%.c $(HDRS)
	@printf "Preprocessing file: "$@" -> "
	@$(CC) $(CFLAGS) -E $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

-include ${DEPENDS}
